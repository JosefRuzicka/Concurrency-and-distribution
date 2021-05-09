// Copyright 2021 Josef Ruzicka <josef.ruzicka@ucr.ac.cr> CC-BY-4
// Outputs the prime numbers that sum the user-given numbers.
// 8/5/2021

// #include <errno.h>
// #include <pthread.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <unistd.h>

// void* run(void* data);
// Method declaration:
int64_t* getInputNumbers(FILE* file, int** inputNumbersSize);
int64_t getLargestNumber(int64_t** inputNumbers, int** inputNumbersSize);
int64_t* sieveOfEratosthenes(int64_t largestInputNumber);
int getSize(int64_t** array);
void goldbachConjecture(int64_t** inputNumbers, int64_t** primeNumbers,
                        int inputNumbersSize, int64_t largestInputNumber);

int main(void) {
  FILE* input = stdin;
  int inputNumbersSize = 0;
  int* inputNumbersSizePtr = &inputNumbersSize;

  // ask user for numbers.
  int64_t* inputNumbers = getInputNumbers(input, &inputNumbersSize);

  // get the largest number from input
  int64_t largestInputNumber =
      getLargestNumber(&inputNumbers, (&inputNumbersSize));

  // get the prime numbers with sieve of Eratosthenes.
  int64_t* primeNumbers = sieveOfEratosthenes(largestInputNumber);

  // Goldbachs Conjecture.
  goldbachConjecture(&inputNumbers, &primeNumbers, inputNumbersSize,
                     largestInputNumber);

  // deallocation of memory.
  free(inputNumbers);
  free(primeNumbers);
  free(inputNumbersSizePtr);
  free(input);
  return 0;
}

// Ask user for numbers and store vthem in dynamic memory.
int64_t* getInputNumbers(FILE* input, int** inputNumbersSize) {
  int64_t value = 0ll;
  int64_t* inputNumbers = calloc(10, sizeof(int64_t));
  int inputNumbersIndex = 0;
  int* inputNumbersSizeReference = *inputNumbersSize;
  printf("Enter numbers to test\n");

  // user inputs numbers until ctrl+D is pressed.
  // the following code is based on the code shown at
  // http://jeisson.ecci.ucr.ac.cr/concurrente/2020c/lecciones/0118/
  // good_programming_practices.mp4, by Jeisson Hidalgo-Cespedes
  while (fscanf(input, "%ld", &value) == 1) {
    // reallocation of memory.
    if (inputNumbersIndex % 10 ==
        0) {  // sizeof(inputNumbers)/sizeof(inputNumbers[0])) {
      inputNumbers = (int64_t*)realloc(
          inputNumbers, (inputNumbersIndex + 10) * sizeof(int64_t));
    }
    // input number is added to the array.
    inputNumbers[inputNumbersIndex] = value;
    inputNumbersIndex++;
    inputNumbersSizeReference = inputNumbersIndex;
  }
  *inputNumbersSize = inputNumbersSizeReference;
  // free(inputNumbersSizeReference);
  return inputNumbers;
}

// calculate all prime numbers from 2 to n and store them in dynamic memory.
int64_t* sieveOfEratosthenes(int64_t largestInputNumber) {
  int64_t* primeNumbers = calloc(largestInputNumber, sizeof(int64_t));
  int64_t* primeNumbersTemp = calloc(largestInputNumber, sizeof(int64_t));

  int primeNumbersIndex = 0;
  int64_t primeNumbersCount = 0;
  bool isPrime = true;

  // dynamic memory structure initialization.
  for (primeNumbersIndex = 2; primeNumbersIndex <= largestInputNumber;
       primeNumbersIndex++) {
    primeNumbers[primeNumbersIndex] = primeNumbersIndex;
    primeNumbersCount++;
    isPrime = true;
    // sieve.
    // https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
    // Adapted from
    // https://technotip.com/7469/c-program-to-find-prime-numbers-from-1-to-300-using-for-loop/
    for (int dividend = 2; dividend <= sqrtl(primeNumbers[primeNumbersIndex]);
         dividend++) {
      if (((llabs(primeNumbers[primeNumbersIndex]) % dividend == 0) &&
           (llabs(primeNumbers[primeNumbersIndex]) != dividend))) {
        isPrime = false;
        goto nextIteration;
      }
    }
  nextIteration:
    if (!isPrime) {
      primeNumbers[primeNumbersIndex] = 0;
      primeNumbersCount--;
    }
  }

  // dynamic memory reallocation to ignore the 0s.
  int primeNumbersTempIndex = 0;
  for (primeNumbersIndex = 2; primeNumbersIndex <= largestInputNumber;
       primeNumbersIndex++) {
    if (primeNumbers[primeNumbersIndex] != 0) {
      primeNumbersTemp[primeNumbersTempIndex] = primeNumbers[primeNumbersIndex];
      primeNumbersTempIndex++;
    }
  }
  free(primeNumbers);
  return primeNumbersTemp;
}

// goldbachs conjecture code.
void goldbachConjecture(int64_t** inputNumbers, int64_t** primeNumbers,
                        int inputNumbersSize, int64_t largestInputNumber) {
  int64_t* inputNumbersReference = *inputNumbers;
  int64_t* primeNumbersReference = *primeNumbers;
  int sumsCount = 0;
  int64_t modulo = 0;
  // go through every input number.
  for (int64_t inputNumbersIndex = 0; inputNumbersIndex < inputNumbersSize;
       inputNumbersIndex++) {
    int64_t* addends = calloc(10, sizeof(int64_t));
    int addendsIndex = 0;
    printf("%ld:", (inputNumbersReference[inputNumbersIndex]));
    sumsCount = 0;
    modulo = (llabs(inputNumbersReference[inputNumbersIndex]) % 2);
    // check if number is in range
    if (llabs(inputNumbersReference[inputNumbersIndex]) <= 5 ||
        llabs(inputNumbersReference[inputNumbersIndex]) >
            (9223372036854775807)) {
      printf(" NA\n");

      // Goldbachs Strong Conjecture
    } else if (modulo == 0) {
      // calculate every possible prime sum to find the goldbachs combinations
      for (int64_t addend1 = 0; addend1 < largestInputNumber; addend1++) {
        for (int64_t addend2 = addend1; addend2 < largestInputNumber;
             addend2++) {
          // check if the sum of addends is equal to the inputNumber.
          if (primeNumbersReference[addend1] != 0 &&
              primeNumbersReference[addend2] != 0) {
            if ((primeNumbersReference[addend1] +
                 primeNumbersReference[addend2]) ==
                llabs(inputNumbersReference[inputNumbersIndex])) {
              if (inputNumbersReference[inputNumbersIndex] < 0) {
                addends[addendsIndex] = primeNumbersReference[addend1];
                addends[addendsIndex + 1] = primeNumbersReference[addend2];
                addendsIndex += 2;

                // reallocation of memory.
                if (addendsIndex % 10 == 0) {
                  addends = (int64_t*)realloc(
                      addends, (addendsIndex * 10) * sizeof(int64_t));
                }
              }
              sumsCount++;
            }
          }
        }
      }
      // printing.
      printf(" %d", sumsCount);
      printf(" sums");
      if (inputNumbersReference[inputNumbersIndex] < 0) {
        printf(": ");
        addendsIndex = 0;
        while (addends[addendsIndex] != 0) {
          if (addendsIndex > 0) {
            printf(", ");
          }
          printf("%ld", addends[addendsIndex]);
          printf(" + ");
          printf("%ld", addends[addendsIndex + 1]);
          addendsIndex += 2;
        }
      }
      printf("\n");

      // Goldbachs Weak Conjecture
    } else {
      // calculate every possible prime sum to find the goldbachs combinations
      for (int64_t addend1 = 0; addend1 < largestInputNumber; addend1++) {
        for (int64_t addend2 = addend1; addend2 < largestInputNumber;
             addend2++) {
          for (int64_t addend3 = addend2; addend3 < largestInputNumber;
               addend3++) {
            // check if the sum of addends is equal to the inputNumber.
            if (primeNumbersReference[addend1] != 0 &&
                primeNumbersReference[addend2] != 0 &&
                primeNumbersReference[addend3] != 0) {
              if (primeNumbersReference[addend1] +
                      primeNumbersReference[addend2] +
                      primeNumbersReference[addend3] ==
                  llabs(inputNumbersReference[inputNumbersIndex])) {
                if (inputNumbersReference[inputNumbersIndex] < 0) {
                  addends[addendsIndex] = primeNumbersReference[addend1];
                  addends[addendsIndex + 1] = primeNumbersReference[addend2];
                  addends[addendsIndex + 2] = primeNumbersReference[addend3];
                  addendsIndex += 3;

                  // reallocation of memory.
                  if (addendsIndex % 9 == 0) {
                    addends = (int64_t*)realloc(
                        addends, (addendsIndex * 9) * sizeof(int64_t));
                  }
                }
                sumsCount++;
              }
            }
          }
        }
      }
      // printing.
      printf(" %d", sumsCount);
      printf(" sums");
      if (inputNumbersReference[inputNumbersIndex] < 0) {
        printf(" : ");
        addendsIndex = 0;
        while (addends[addendsIndex] != 0) {
          if (addendsIndex > 0) {
            printf(", ");
          }
          printf("%ld", addends[addendsIndex]);
          printf(" + ");
          printf("%ld", addends[addendsIndex + 1]);
          printf(" + ");
          printf("%ld", addends[addendsIndex + 2]);
          addendsIndex += 3;
        }
      }
      printf("\n");
    }
    free(addends);
  }
}

// find largest number in order to call sieveOfEratosthenes
int64_t getLargestNumber(int64_t** inputNumbers, int** inputNumbersSize) {
  int64_t largestInputNumber = 0;
  int64_t* inputNumbersReference = *inputNumbers;
  // int* inputNumbersSizeReference = *inputNumbersSize;
  for (int index = 0; index < (int)*inputNumbersSize; index++) {
    // for (int index = 0; index < inputNumbersSize; index++) {
    if ((llabs(inputNumbersReference[index]) > largestInputNumber) &&
        (llabs(inputNumbersReference[index] <= (9223372036854775807)))) {
      largestInputNumber = llabs(inputNumbersReference[index]);
    }
  }
  // free(inputNumbersReference);
  return largestInputNumber;
}
