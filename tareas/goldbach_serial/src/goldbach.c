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
int64_t* getInputNumbers(FILE* file, int* inputNumbersSize);
int64_t getLargestNumber(int64_t** inputNumbers, int* inputNumbersSize);
int64_t* sieveOfEratosthenes(int64_t largestInputNumber);
int getSize(int64_t* array);
void goldbachConjecture(int64_t** inputNumbers, int64_t** primeNumbers,
                        int inputNumbersSize, int64_t largestInputNumber);

/**
 * @brief Calls method to calculate Goldbachs conjecture numbers.
 */
int main(void) {
  FILE* input = stdin;
  int inputNumbersSize = 0;

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
  return 0;
}

/**
 * @brief Ask user for numbers and returns them stored in dynamic memory.
 * @details
 *  @code
 *    FILE* input = stdin;
 *    int inputNumbersSize = 0;
 *    int* inputNumbersSizePtr = &inputNumbersSize;
 *    int64_t* numbers = getInputNumbers(input, &inputSize);
 *  \endcode
 * @param input: The numbers to be calculated as Goldbach sums.
 * @param inputNumbersSize: The amount of input numbers.
 */
int64_t* getInputNumbers(FILE* input, int* inputNumbersSize) {
  int64_t value = 0ll;
  int64_t* inputNumbers = calloc(10, sizeof(int64_t));
  int inputNumbersIndex = 0;
  int* inputNumbersSizeReference = inputNumbersSize;
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
    inputNumbersSizeReference = &inputNumbersIndex;
  }
  *inputNumbersSize = *inputNumbersSizeReference;
  // free(inputNumbersSizeReference);
  return inputNumbers;
}

/**
 * @brief Returns prime numbers from 2 to n in dynamic memory.
 * @details
 *  @code
 *    int64_t largestInputNumber = 10
 *    int64_t* primeNumbers = sieveOfEratosthenes(largestInputNumber);
 *  \endcode
 * @param largestInputNumber: the range to which prime numbers will be
 * calculated.
 */
int64_t* sieveOfEratosthenes(int64_t largestInputNumber) {
  int64_t* primeNumbers = calloc(largestInputNumber + 1, sizeof(int64_t));
  int64_t* primeNumbersTemp = calloc(largestInputNumber + 1, sizeof(int64_t));

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

/**
 * @brief prints the goldbach sums that add up to the input numbers.
 * @details
 *  @code
 *    FILE* input = stdin;
 *    int inputNumbersSize = 10;
 *    int largestInputNumber = 10;
 *    int64_t* primeNumbers = {2, 3, 5, 7}
 *    void goldbachConjecture(&inputNumbers, &primeNumbers, inputNumbersSize,
 *                            largestInputNumber);
 *  \endcode
 * @param inputNumbers: The numbers to be calculated as Goldbach sums..
 * @param primeNumbers: The prime numbers.
 * @param inputNumbersSize: The amount of inputNumbers.
 * @param largestInputNumber: The largest input number.
 */
void goldbachConjecture(int64_t** inputNumbers, int64_t** primeNumbers,
                        int inputNumbersSize, int64_t largestInputNumber) {
  int64_t* inputNumbersReference = *inputNumbers;
  int64_t* primeNumbersReference = *primeNumbers;
  int sumsCount = 0;
  int addendsIndex = 0;
  int addendsCount = 0;
  int64_t modulo = 0;
  // int64_t* addends = calloc(10, sizeof(int64_t));
  // go through every input number.
  for (int64_t inputNumbersIndex = 0; inputNumbersIndex < inputNumbersSize;
       inputNumbersIndex++) {
    int64_t* addends = calloc(10, sizeof(int64_t));
    // addends = calloc(10, sizeof(int64_t));
    addendsIndex = 0;
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
        addendsCount = addendsIndex;
        addendsIndex = 0;
        while (addendsIndex < addendsCount) {
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
        addendsCount = addendsIndex;
        addendsIndex = 0;
        while (addendsIndex < addendsCount) {
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
  // free(addends);
}

/**
 * @brief Returns largest number from an array.
 * @details
 *  @code
 *    int64_t* inputNumbers = {1, 2, 3, 4, 5};
 *    int inputNumbersSize = 5;
 *    int64_t* largestNumber = getLargestNumber(&inputNumbers,
 *                                              &inputNumbersSize);
 *  \endcode
 * @param inputNumbers: The number array.
 * @param inputNumbersSize: The size of the array.
 */
int64_t getLargestNumber(int64_t** inputNumbers, int* inputNumbersSize) {
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
