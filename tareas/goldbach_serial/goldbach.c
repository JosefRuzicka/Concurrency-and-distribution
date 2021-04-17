// Copyright 2021 Josef Ruzicka <josef.ruzicka@ucr.ac.cr> CC-BY-4
// Outputs the prime numbers that sum the user-given numbers.

// #include <errno.h>
// #include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
// #include <unistd.h>

// void* run(void* data);
int64_t* getInputNumbers(FILE* file);
int64_t getLargestNumber(int64_t* inputNumbers);
int64_t* sieveOfEratosthenes(int64_t largestInputNumber);
void goldbachConjecture(int64_t* inputNumbers, int64_t* primeNumbers);

int main(void) {
  FILE* input = stdin;
  int64_t* inputNumbers = getInputNumbers(input);
  int64_t* primeNumbers = sieveOfEratosthenes(getLargestNumber(inputNumbers));
  printf("---------\n");
  goldbachConjecture(inputNumbers, primeNumbers);
  // deallocation of memory.
  free(inputNumbers);
  free(primeNumbers);
  return 0;
}

// Ask user for numbers and store them in dynamic memory.
int64_t* getInputNumbers(FILE* input) {
  int64_t value = 0ll;
  int64_t* inputNumbers = malloc(10 * sizeof(int64_t));
  int inputNumbersIndex = 0;
  printf("Enter numbers to test\n");
  
  // user inputs numbers until ctrl+D is pressed.
  // the following code is based on the code shown at
  // http://jeisson.ecci.ucr.ac.cr/concurrente/2020c/lecciones/0118/
  // good_programming_practices.mp4, by Jeisson Hidalgo-Cespedes
  while (fscanf(input,"%ld", &value) == 1) {
	  
	// reallocation of memory.
    if (inputNumbersIndex == sizeof(inputNumbers)/**sizeof(inputNumbers[0])**/) {
	  inputNumbers = (int64_t*) realloc(inputNumbers, sizeof(inputNumbers) + 10 * sizeof(int64_t));
	}
	// input number is added to the array.
    inputNumbers[inputNumbersIndex] = value;
    inputNumbersIndex++;
  }
  return inputNumbers;
}

// calculate all prime numbers from 2 to n and store them in dynamic memory.
int64_t* sieveOfEratosthenes(int64_t largestInputNumber) {
	int64_t* primeNumbers = malloc(largestInputNumber * sizeof(int64_t));
  int primeNumbersIndex = 0;
  int primeNumbersCount = 0;
	
	// dynamic memory structure initialization.
	for (primeNumbersIndex = 2; primeNumbersIndex <= largestInputNumber;
			 primeNumbersIndex++) {
		primeNumbers[primeNumbersIndex] = primeNumbersIndex;
		primeNumbersCount++;
	}
	
	// sieve
	for (primeNumbersIndex = 2; primeNumbersIndex <= largestInputNumber;
  primeNumbersIndex++){
		if (((primeNumbers[primeNumbersIndex] %2 == 0) && (primeNumbers[primeNumbersIndex] != 2))
		||  ((primeNumbers[primeNumbersIndex] %3 == 0) && (primeNumbers[primeNumbersIndex] != 3))
		||  ((primeNumbers[primeNumbersIndex] %5 == 0) && (primeNumbers[primeNumbersIndex] != 5))
		||  ((primeNumbers[primeNumbersIndex] %7 == 0) && (primeNumbers[primeNumbersIndex] != 7))) {
			primeNumbers[primeNumbersIndex] = 0;
			primeNumbersCount--;
		}
	}
	
	// dynamic memory reallocation to ignore the 0s.
	int64_t* primeNumbersTemp = malloc(primeNumbersCount* sizeof(int64_t));
	int primeNumbersTempIndex = 0;
	for (primeNumbersIndex = 2; primeNumbersIndex <= largestInputNumber; primeNumbersIndex++) {
	  if (primeNumbers[primeNumbersIndex] != 0){
			primeNumbersTemp[primeNumbersTempIndex] = primeNumbers[primeNumbersIndex];
			primeNumbersTempIndex++;
		}
	}
	free(primeNumbers);
	return primeNumbersTemp;
}

void goldbachConjecture(int64_t* inputNumbers, int64_t* primeNumbers) {
	int sumsCount = 0;
	int module = 0;
	// go through every input number.
	for (long unsigned int inputNumbersIndex = 0; inputNumbersIndex < sizeof(inputNumbers);
	inputNumbersIndex++){
		printf("%ld", inputNumbers[inputNumbersIndex]);
		sumsCount = 0;
		module = inputNumbers[inputNumbersIndex]%2;
		// check if number is in range
		if (inputNumbers[inputNumbersIndex] <= 5 /*|| inputNumbers[inputNumbersIndex] > 2^63-1**/) {
			printf(": NA\n");
		}
		// Goldbachs Strong Conjecture
		else if(module == 0){
			for (long unsigned int addend1 = 0; addend1 < sizeof(primeNumbers); addend1++) {
				for (long unsigned int addend2 = addend1; addend2 < sizeof(primeNumbers); addend2++) {
					if (primeNumbers[addend1] + primeNumbers[addend2] == inputNumbers[inputNumbersIndex]) {
						//if (inputNumbers[inputNumberIndex] < 0){
						//	sumsToPrintTemp = ("%ld", addend1 + " %ld\n", addend2);
						//	sumsToPrint = sumsToPrint + sumsToPrintTemp;
						//}
						sumsCount++;
					}
				}
			}
			printf(" sums : ");
			printf("%d\n", sumsCount);	
		}
		
		// Goldbachs Weak Conjecture
		else{
			for (long unsigned int addend1 = 0; addend1 < sizeof(primeNumbers); addend1++) {
				for (long unsigned int addend2 = addend1; addend2 < sizeof(primeNumbers); addend2++) {
					for (long unsigned int addend3 = addend2; addend3 < sizeof(primeNumbers); addend3++) {
					  if (primeNumbers[addend1] + primeNumbers[addend2] 
					    + primeNumbers[addend3] == inputNumbers[inputNumbersIndex]) {
						  //if (inputNumbers[inputNumberIndex] < 0){
						  //	sumsToPrintTemp = ("%ld", addend1 + " %ld\n", addend2);
						  //	sumsToPrint = sumsToPrint + sumsToPrintTemp;
						  //}
						  sumsCount++;
						}
					}
				}
			}
			printf(" sums : ");
			printf("%d\n", sumsCount);	
		}
	}
}

//find largest number in order to call sieveOfEratosthenes
int64_t getLargestNumber(int64_t* inputNumbers) {
  int largestInputNumber = 0;
  for (long unsigned int index = 0; index < sizeof(inputNumbers); index++) {
    if ((inputNumbers[index] > largestInputNumber) || (inputNumbers[index])*-1 > largestInputNumber){
      largestInputNumber = inputNumbers[index];
    }
  }
  return largestInputNumber;
}
