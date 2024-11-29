package main

import (
	"fmt"
	"time"
)

func ex1() {
	channel := make(chan string)

	go func() {
		channel <- "Hello"
	}()

	fmt.Println(<-channel)
}

func ex2() {
	channel := make(chan string)

	go func() {
		channel <- "Message #1"
		channel <- "Message #2"
	}()

	fmt.Println(<-channel + "\n" + <-channel)
}

func ex3() {
	success := make(chan bool)

	go func() {
		fmt.Println("Started processing...")
		time.Sleep(2 * time.Second)
		fmt.Println("Finished processing!")

		success <- true
	}()

	<-success
	fmt.Println("Notification received!")
}

func ex4() {
	in_chan := make(chan string)
	out_chan := make(chan string)

	go func() {
		in_chan <- "input message"
	}()

	go func() {
		out_chan <- "got " + <-in_chan
	}()

	fmt.Println(<-out_chan)
}

func sendTime(channel chan<- string) {
	channel <- "Done at " + time.Now().String()[:19]
}

func ex5() {
	chan1 := make(chan string)
	chan2 := make(chan string)

	go func() {
		time.Sleep(2 * time.Second)
		sendTime(chan1)
	}()

	go func() {
		sendTime(chan2)
		time.Sleep(4 * time.Second)
		sendTime(chan2)
	}()

	for i := 0; i < 3; i++ {
		select {
			case msg := <-chan1:
				fmt.Println(msg)
			case msg := <-chan2:
				fmt.Println(msg)
		}
	}
}

func ex6() {
	result := make(chan int)
	go func (a, b int, channel chan<- int) {
		for b != 0 {
			a, b = b, a % b
		}
		time.Sleep(time.Minute / 40)
		channel <- a
	}(28, 63, result)

	select {
		case res := <-result:
			fmt.Println(res)
		case <-time.After(2 * time.Second):
			fmt.Println("Timeout")
	}
}

func main() {
	fmt.Println("< Lab 02 >")
	exercises := []func(){ex1, ex2, ex3, ex4, ex5, ex6}
	for i := 0; i < len(exercises); i++ {
		fmt.Printf("[%d] Ex %d\n", i + 1, i + 1)
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
