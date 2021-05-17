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

#include "array_int64_t.h"
// #include <unistd.h>

// Method declaration:
int getInputNumbers(FILE* file, array_int64_t_t* inputNumbers);
int64_t getLargestNumber(array_int64_t_t* inputNumbers);
int sieveOfEratosthenes(array_int64_t_t* primeNumbers,
                        int64_t largestInputNumber);
int getSize(array_int64_t_t array);
int goldbachConjecture(array_int64_t_t* inputNumbers,
                       array_int64_t_t* primeNumbers);

/**
 * @brief Calls method to calculate Goldbachs conjecture numbers.
 */
int main(void) {
  FILE* input = stdin;

  // ask user for numbers.
  array_int64_t_t inputNumbers;
  array_int64_t_init(&inputNumbers);
  getInputNumbers(input, &inputNumbers);

  // get the largest number from input
  int64_t largestInputNumber = getLargestNumber(&inputNumbers);

  // get the prime numbers with sieve of Eratosthenes.
  array_int64_t_t primeNumbers;
  array_int64_t_init(&primeNumbers);
  sieveOfEratosthenes(&primeNumbers, largestInputNumber);

  // Goldbachs Conjecture.
  goldbachConjecture(&inputNumbers, &primeNumbers);

  // deallocation of memory.
  array_int64_t_destroy(&inputNumbers);
  array_int64_t_destroy(&primeNumbers);
  return 0;
}

/**
 * @brief Ask user for numbers and stores them in dynamic memory.
 * @details
 *  @code
 *    FILE* input = stdin;
 *    array_int64_t_t inputNumbers;
 * array_int64_t_init(&inputNumbers);
 *    int64_t* numbers = getInputNumbers(input, &inputNumbers);
 *  \endcode
 * @param input: The numbers to be calculated as Goldbach sums.
 * @param inputNumbersS: The array of int_64_t on which the input numbers will
 * be stored.
 */
int getInputNumbers(FILE* input, array_int64_t_t* inputNumbers) {
  int64_t value = 0ll;
  printf("Enter numbers to test\n");

  // user inputs numbers until ctrl+D is pressed.
  // the following code is based on the code shown at
  // http://jeisson.ecci.ucr.ac.cr/concurrente/2020c/lecciones/0118/
  // good_programming_practices.mp4, by Jeisson Hidalgo-Cespedes
  while (fscanf(input, "%ld", &value) == 1) {
    // input number is added to the array.
    if (array_int64_t_append(inputNumbers, value) == EXIT_FAILURE) {
      return EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;
}

/**
 * @brief stores prime numbers from 2 to n in dynamic memory.
 * @details
 *  @code
 *    array_int64_t_t primeNumbers;
 *    array_int64_t_init(&primeNumbers);
 *    int64_t largestInputNumber = 10
 *    sieveOfEratosthenes(&primeNumbers, largestInputNumber);
 *  \endcode
 * @param primeNumbers: array of int64_t on which prime numbers will be stored.
 * @param largestInputNumber: the range to which prime numbers will be
 * calculated.
 */
int sieveOfEratosthenes(array_int64_t_t* primeNumbers,
                        int64_t largestInputNumber) {
  // this array will hold the prime numbers at their index and 0s at the indexes
  // of numbers that are not prime. for example: {0, 0, 2, 3, 0, 5, 0, 7}
  if (primeNumbers) {
    array_int64_t_t primeNumbersTemp;
    array_int64_t_init(&primeNumbersTemp);

    int primeNumbersIndex = 0;
    int64_t primeNumbersCount = 0;
    bool isPrime = true;

    // dynamic memory structure initialization.
    array_int64_t_append(&primeNumbersTemp, 0);
    array_int64_t_append(&primeNumbersTemp, 0);
    for (primeNumbersIndex = 2; primeNumbersIndex <= largestInputNumber;
         primeNumbersIndex++) {
      array_int64_t_append(&primeNumbersTemp, primeNumbersIndex);
      primeNumbersCount++;
      isPrime = true;
      // sieve.
      // https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
      // Adapted from
      // https://technotip.com/7469/c-program-to-find-prime-numbers-from-1-to-300-using-for-loop/
      for (int dividend = 2;
           dividend <= sqrtl(primeNumbersTemp.elements[primeNumbersIndex]);
           dividend++) {
        if (((llabs(primeNumbersTemp.elements[primeNumbersIndex]) % dividend ==
              0) &&
             (llabs(primeNumbersTemp.elements[primeNumbersIndex]) !=
              dividend))) {
          isPrime = false;
          goto nextIteration;
        }
      }
    nextIteration:
      if (!isPrime) {
        primeNumbersTemp.elements[primeNumbersIndex] = 0;
        primeNumbersCount--;
      }
    }

    // dynamic memory reallocation to ignore the 0s.
    int primeNumbersTempIndex = 0;
    for (primeNumbersIndex = 2; primeNumbersIndex <= largestInputNumber;
         primeNumbersIndex++) {
      if (primeNumbersTemp.elements[primeNumbersIndex] != 0) {
        array_int64_t_append(primeNumbers,
                             primeNumbersTemp.elements[primeNumbersIndex]);
        primeNumbersTempIndex++;
      }
    }
    array_int64_t_destroy(&primeNumbersTemp);
  } else {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

/**
 * @brief prints the goldbach sums that add up to the input numbers.
 * @details
 *  @code
 *    int64_t* inputNumbers = {5, 8, -7, 6};
 *    int64_t* primeNumbers = {2, 3, 5, 7};
 *    void goldbachConjecture(&inputNumbers, &primeNumbers);
 *  \endcode
 * @param inputNumbers: The numbers to be calculated as Goldbach sums..
 * @param primeNumbers: The prime numbers.
 */
int goldbachConjecture(array_int64_t_t* inputNumbers,
                       array_int64_t_t* primeNumbers) {
  int sumsCount = 0;
  int addendsIndex = 0;
  int addendsCount = 0;
  int64_t modulo = 0;
  // go through every input number.
  if (inputNumbers && primeNumbers) {
    for (int64_t inputNumbersIndex = 0;
         inputNumbersIndex < (int)inputNumbers->count; inputNumbersIndex++) {
      array_int64_t_t addends;
      array_int64_t_init(&addends);
      addendsIndex = 0;
      printf("%ld:", (inputNumbers->elements[inputNumbersIndex]));
      sumsCount = 0;
      modulo = (llabs(inputNumbers->elements[inputNumbersIndex]) % 2);
      // check if number is in range
      if (llabs(inputNumbers->elements[inputNumbersIndex]) <= 5 ||
          llabs(inputNumbers->elements[inputNumbersIndex]) >
              (9223372036854775807)) {
        printf(" NA\n");

        // Goldbachs Strong Conjecture
      } else if (modulo == 0) {
        // calculate every possible prime sum to find the goldbachs
        // combinations
        for (int64_t addend1 = 0; addend1 < (int)primeNumbers->count;
             addend1++) {
          for (int64_t addend2 = addend1; addend2 < (int)primeNumbers->count;
               addend2++) {
            // check if the sum of addends is equal to the inputNumber.
            if (primeNumbers->elements[addend1] != 0 &&
                primeNumbers->elements[addend2] != 0) {
              if ((primeNumbers->elements[addend1] +
                   primeNumbers->elements[addend2]) ==
                  llabs(inputNumbers->elements[inputNumbersIndex])) {
                if (inputNumbers->elements[inputNumbersIndex] < 0) {
                  array_int64_t_append(&addends,
                                       primeNumbers->elements[addend1]);
                  array_int64_t_append(&addends,
                                       primeNumbers->elements[addend2]);
                  addendsIndex += 2;
                }
                sumsCount++;
              }
            }
          }
        }
        // printing.
        printf(" %d", sumsCount);
        printf(" sums");
        if (inputNumbers->elements[inputNumbersIndex] < 0) {
          printf(": ");
          addendsCount = addendsIndex;
          addendsIndex = 0;
          while (addendsIndex < addendsCount) {
            if (addendsIndex > 0) {
              printf(", ");
            }
            printf("%ld", addends.elements[addendsIndex]);
            printf(" + ");
            printf("%ld", addends.elements[addendsIndex + 1]);
            addendsIndex += 2;
          }
        }
        printf("\n");

        // Goldbachs Weak Conjecture
      } else {
        // calculate every possible prime sum to find the goldbachs
        // combinations
        for (int64_t addend1 = 0; addend1 < (int)primeNumbers->count;
             addend1++) {
          for (int64_t addend2 = addend1; addend2 < (int)primeNumbers->count;
               addend2++) {
            for (int64_t addend3 = addend2; addend3 < (int)primeNumbers->count;
                 addend3++) {
              // check if the sum of addends is equal to the inputNumber.
              if (primeNumbers->elements[addend1] != 0 &&
                  primeNumbers->elements[addend2] != 0 &&
                  primeNumbers->elements[addend3] != 0) {
                if (primeNumbers->elements[addend1] +
                        primeNumbers->elements[addend2] +
                        primeNumbers->elements[addend3] ==
                    llabs(inputNumbers->elements[inputNumbersIndex])) {
                  if (inputNumbers->elements[inputNumbersIndex] < 0) {
                    array_int64_t_append(&addends,
                                         primeNumbers->elements[addend1]);
                    array_int64_t_append(&addends,
                                         primeNumbers->elements[addend2]);
                    array_int64_t_append(&addends,
                                         primeNumbers->elements[addend3]);
                    addendsIndex += 3;
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
        if (inputNumbers->elements[inputNumbersIndex] < 0) {
          printf(" : ");
          addendsCount = addendsIndex;
          addendsIndex = 0;
          while (addendsIndex < addendsCount) {
            if (addendsIndex > 0) {
              printf(", ");
            }
            printf("%ld", addends.elements[addendsIndex]);
            printf(" + ");
            printf("%ld", addends.elements[addendsIndex + 1]);
            printf(" + ");
            printf("%ld", addends.elements[addendsIndex + 2]);
            addendsIndex += 3;
          }
        }
        printf("\n");
      }
      array_int64_t_destroy(&addends);
    }
  } else {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

/**
 * @brief Returns largest number from an array.
 * @details
 *  @code
 *    int64_t* inputNumbers = {1, 2, 3, 4, 5};
 *    int64_t* largestNumber = getLargestNumber(&inputNumbers);
 *  \endcode
 * @param inputNumbers: The number array of int64_t.
 */
int64_t getLargestNumber(array_int64_t_t* inputNumbers) {
  int64_t largestInputNumber = 0;
  for (int index = 0; index < (int)inputNumbers->count; index++) {
    if ((llabs(inputNumbers->elements[index]) > largestInputNumber) &&
        (llabs(inputNumbers->elements[index] <= (9223372036854775807)))) {
      largestInputNumber = llabs(inputNumbers->elements[index]);
    }
  }
  return largestInputNumber;
}
