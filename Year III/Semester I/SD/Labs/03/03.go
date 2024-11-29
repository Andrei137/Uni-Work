package main

import (
	"bufio"
	"encoding/json"
	"fmt"
	"io"
	"net/http"
	"os"
	"regexp"
	"strconv"
	"strings"
)

// Part 01

// Ex 01
func exists(path string) bool {
	_, err := os.Stat(path)
	return err == nil
}

// Ex 02
func check(err error) {
	if err != nil {
		panic(err.Error())
	}
}

// Ex 03
func readToString(filePath string) string {
	content, err := os.ReadFile(filePath)
	check(err)
	return string(content)
}

// Ex 04
func getFile(filePath string) *os.File {
	file, err := os.Open(filePath)
	check(err)
	return file
}

func readToArray(file *os.File) []string {
	var lines []string
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		lines = append(lines, scanner.Text())
	}
	check(scanner.Err())
	return lines
}

// Ex 05
func writeData(filePath string, content []string) {
	check(os.WriteFile(filePath, []byte(strings.Join(content, "\n")), 0644))
}

// Ex 06
func renameFile(oldFilePath string, newFilePath string) {
	check(os.Rename(oldFilePath, newFilePath))
}

func part1() {
	inputPath := "txt/read_me.txt"
	oldOutputPath := "txt/rename_me.txt"
	newOutputPath := "txt/output.txt"

	if !exists(inputPath) {
		fmt.Println("The file " + inputPath + " does not exist!")
		return
	}

	newInputPath := readToString(inputPath)

	file := getFile("txt/" + newInputPath)
	defer file.Close()

	writeData(oldOutputPath, readToArray(file))
	renameFile(oldOutputPath, newOutputPath)
}

// Part 02
func printMatching(regex *regexp.Regexp, text string) {
	for _, match := range regex.FindAllString(text, -1) {
		fmt.Println(match)
	}
}

func part2() {
	inputPath := "txt/regex.txt"
	regex := regexp.MustCompile(`[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}\s`)

	file := getFile(inputPath)
	content := readToArray(file)
	defer file.Close()

	contentString := strings.Join(content, " ")
	printMatching(regex, contentString)
}

// Part 03
type Date struct {
	Day int `json:"day"`
	Month int `json:"month"`
	Year int `json:"year"`
}

type Person struct {
	FirstName string `json:"firstname"`
	LastName string `json:"lastname"`
	Id int `json:"id"`
	Married bool `json:"married"`
	BirthDate Date `json:"birthdate"`
}

func encode(data interface{}) []byte {
	jsonData, err := json.Marshal(data)
	check(err)
	return jsonData
}

func decode[T any](jsonData []byte, output *T) {
	check(json.Unmarshal(jsonData, output))
}

func part3() {
	date := Date{1, 1, 1995}
	person := Person{"John", "Doe", 1337, true, Date{1, 1, 1990}}

	dateEncoded := encode(date)
	personEncoded := encode(person)

	var dateDecoded Date
	var personDecoded Person
	decode(dateEncoded, &dateDecoded)
	decode(personEncoded, &personDecoded)

	fmt.Println("The encoded date:", string(dateEncoded))
	fmt.Println("Is the date decoded correctly?", date == dateDecoded)
	fmt.Println("The encoded person:", string(personEncoded))
	fmt.Println("Is the person decoded correctly?", person == personDecoded)
}

// Part 04
func requestSite(url string) string {
	response, err := http.Get(url)
	check(err)
	defer response.Body.Close()

	body, err := io.ReadAll(response.Body)
	check(err)

	return string(body)
}

func hello(w http.ResponseWriter, req *http.Request) {
	req.ParseForm()

	name := req.Form.Get("name")
	if name == "" {
		name = "world"
	}

	fmt.Fprintf(w, "Hello, %s!\n", name)
}

func add(w http.ResponseWriter, req *http.Request) {
	req.ParseForm()
	a, err := strconv.Atoi(req.Form.Get("a"))
	check(err)
	b, err := strconv.Atoi(req.Form.Get("b"))
	check(err)

	fmt.Fprintf(w, "%d + %d = %d\n", a, b, (a + b))
}

func server() {
	http.HandleFunc("/hello", hello)
	http.HandleFunc("/add", add)
	http.ListenAndServe(":8080", nil)
}

func part4() {
	url := "https://example.com/"
	outputPath := "txt/output.html"

	writeData(outputPath, []string{requestSite(url)})
	server()
}

func main() {
	fmt.Println("< Lab 03 >")
	exercises := []func(){part1, part2, part3, part4}
	for i := 0; i < len(exercises); i++ {
		fmt.Printf("[%d] Part %d\n", i + 1, i + 1)
	}
	fmt.Printf("[0] Exit\n-> ")

	var choice int
	fmt.Scanln(&choice)

	if choice < 1 || choice > len(exercises) {
		if choice != 0 {
			fmt.Println("Invalid choice!")
		}
		return
	}

	exercises[choice - 1]()
}