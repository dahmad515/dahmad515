package main

import (
  "bufio"
  "fmt"
  "os"
  "strings"
)

func main() {
	var casesCountPak, casesCountSouthKorea, casesCountFrance = 1526, 9583, 37575
	var check = 0
	var count = 3
	
	
	for check < 1 {
		fmt.Println("Please select an option: \n")
		fmt.Println("1 - Covid cases in Pakistan \n")
		fmt.Println("2 - Covid cases in South Korea \n")
		fmt.Println("3 - Covid cases in France \n")
		fmt.Println("4 - Print my personalised message for Corona virus \n")
		fmt.Println("0 - Exit \n")
		
		reader := bufio.NewReader(os.Stdin)
		userInput1, _ := reader.ReadString('\n')
		userInput := strings.Trim(userInput1, " ")
		fmt.Println("userInput = ", userInput)
		
		if strings.Compare(userInput, "1") == 1{
			fmt.Println("Covid cases in Pakistan =  ", casesCountPak, "\n")
			count--
		}
		if strings.Compare(userInput, "2") == 1{
			fmt.Println("Covid cases in South Korea =  ", casesCountSouthKorea, "\n")
			count--
		}
		if strings.Compare(userInput, "3") == 1{
			fmt.Println("Covid cases in France =  ", casesCountFrance, "\n")
			count--
		}
		if strings.Compare(userInput, "4") == 1{
			fmt.Println("Fasla rakhain, warna corona ho jayega !!")
		}
		if strings.Compare(userInput, "0") == 1{
			if count <= 0{
				check = 0
			} else {
				fmt.Println("View the cases of all the countries first")
			}
		} else{
			fmt.Println("Invalid Input")
		}
		
	}
	
	
	
	}




