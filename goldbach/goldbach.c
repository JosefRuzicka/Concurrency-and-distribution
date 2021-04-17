// Copyright 2021 Josef Ruzicka <josef.ruzicka@ucr.ac.cr> CC-BY-4
// Outputs the prime numbers that sum the user-given numbers.

//#include <errno.h>
//#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
//#include <unistd.h>

//void* run(void* data);
long long int* getInputNumbers(FILE* file);
long long int* sieveOfEratosthenes(long long int largestPrime);

int main(void) {
  FILE* input = stdin;
  long long int* inputNumbers = getInputNumbers(input);
  long long int* primeNumbers = sieveOfEratosthenes(30);
  
  // reading.
  printf("---------\n");
  printf("Prime Numbers test:\n");
	//printf("%lld\n", inputNumbers[1]);
	printf("%lld\n", primeNumbers[1]);
	printf("%lld\n", primeNumbers[2]);
	printf("%lld\n", primeNumbers[3]);
	printf("%lld\n", primeNumbers[4]);
	printf("%lld\n", primeNumbers[5]);
	printf("%lld\n", primeNumbers[6]);

  // deallocation of memory.
  free(inputNumbers);
  free(primeNumbers);
  return 0;
}

// Ask user for numbers and store them in dynamic memory.
long long int* getInputNumbers(FILE* input){
	long long int value = 0ll;
  long long int* inputNumbers = malloc(10 * sizeof(long long int));
  int inputNumbersIndex = 0;
  
  printf("Enter numbers to test\n");
    
  // user inputs numbers until ctrl+D is pressed.
  // the following code is based on the code shown at
  // http://jeisson.ecci.ucr.ac.cr/concurrente/2020c/lecciones/0118/
  // good_programming_practices.mp4, by Jeisson Hidalgo-Cespedes
  while (fscanf(input,"%lld", &value) == 1){
	  
	// reallocation of memory.
    if (inputNumbersIndex == sizeof(inputNumbers)/
									 sizeof(inputNumbers[0])){
	  inputNumbers = (long long int*) realloc(inputNumbers
						   ,sizeof(inputNumbers) * 10);
	}
	// input number is added to the array.
    inputNumbers[inputNumbersIndex] = value;
    inputNumbersIndex++;
  }
  return inputNumbers;
}

// calculate all prime numbers from 2 to n and store them in dynamic memory.
long long int* sieveOfEratosthenes(long long int largestPrime){
	long long int* primeNumbers = malloc(largestPrime * sizeof(long long int));
  int primeNumbersIndex = 0;
  int primeNumbersCount = 0;
	
	
	// dynamic memory structure initialization.
	for (primeNumbersIndex = 2; primeNumbersIndex <= largestPrime;
			 primeNumbersIndex++){
		primeNumbers[primeNumbersIndex] = primeNumbersIndex;
		primeNumbersCount++;
	}
	// sieve
	for (primeNumbersIndex = 2; primeNumbersIndex <= largestPrime;
  primeNumbersIndex++){
		if (primeNumbers[primeNumbersIndex] %2 == 0 && primeNumbers[primeNumbersIndex] != 2
		||  primeNumbers[primeNumbersIndex] %3 == 0 && primeNumbers[primeNumbersIndex] != 3
		||  primeNumbers[primeNumbersIndex] %5 == 0 && primeNumbers[primeNumbersIndex] != 5
		||  primeNumbers[primeNumbersIndex] %7 == 0 && primeNumbers[primeNumbersIndex] != 7){
			primeNumbers[primeNumbersIndex] = 0;
			primeNumbersCount--;
		}
	}
	
	// dynamic memory reallocation to ignore the 0s.
	long long int* primeNumbersTemp = malloc(primeNumbersCount* sizeof(long long int));
	int primeNumbersTempIndex = 0;
	for (primeNumbersIndex = 2; primeNumbersIndex <= largestPrime; primeNumbersIndex++){
	  if (primeNumbers[primeNumbersIndex] != 0){
			primeNumbersTemp[primeNumbersTempIndex] = primeNumbers[primeNumbersIndex];
			primeNumbersTempIndex++;
		}
	}
	free(primeNumbers);
	return primeNumbersTemp;
}
	
