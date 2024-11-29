package main

import (
	"fmt"
)

func sum(nums []int, channel chan<- int) {
	sum := 0
	for _, num := range nums {
		sum += num
	}
	channel <- sum
}

func ex1(nums []int) int {
	sumChan := make(chan int)
	
	go sum(nums, sumChan);

	return <-sumChan
}

func ex2(nums []int) int {
	firstHalf := make(chan int)
	secondHalf := make(chan int)
	m := len(nums) / 2

	go sum(nums[:m], firstHalf)
	go sum(nums[m:], secondHalf)

	return <-firstHalf + <-secondHalf
}

func main() {
	fmt.Println("< Lab 04 >")
	exercises := [](func([]int) int){ex1, ex2}
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
	nums := []int{1, 2, 3, 4, 5}
	fmt.Println(exercises[choice - 1](nums))
}
