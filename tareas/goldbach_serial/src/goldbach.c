// Copyright 2021 Josef Ruzicka <josef.ruzicka@ucr.ac.cr> CC-BY-4
// Calculates the goldbach Sums of the user-input numbers.
// 17/5/2021

#include "goldbach.h"

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array_int64_t.h"
#include "input_output.h"

// stores prime numbers from 2 to n in dynamic memory.
int sieveOfEratosthenes(array_int64_t_t* primeNumbers,
                        int64_t largestInputNumber) {
  assert(primeNumbers);
  if (primeNumbers) {
    bool isPrime = true;
    // Fill array with primes from 2 to largestInputNumber
    for (int64_t currentPrimeNumber = 2;
         currentPrimeNumber <= largestInputNumber; currentPrimeNumber++) {
      isPrime = true;
      // sieve.
      // https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
      // Adapted from
      // https://technotip.com/7469/c-program-to-find-prime-numbers-from-1-to-300-using-for-loop/
      for (int dividend = 2; dividend <= sqrtl(currentPrimeNumber);
           dividend++) {
        if ((currentPrimeNumber % dividend == 0) &&
            (currentPrimeNumber != dividend)) {
          isPrime = false;
          goto nextIteration;
        }
      }
    nextIteration:
      // if the number is prime. add it to the array.
      if (isPrime) {
        array_int64_t_append(primeNumbers, currentPrimeNumber);
      }
    }
  } else {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

// prints the goldbach sums that add up to the input numbers.
int goldbachConjecture(array_int64_t_t* inputNumbers,
                       array_int64_t_t* primeNumbers) {
  assert(inputNumbers);
  assert(primeNumbers);
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
        goldbachStrongConjecture(inputNumbers, primeNumbers, &addends,
                                 inputNumbersIndex, addendsIndex, sumsCount,
                                 addendsCount);
        // Goldbachs Weak Conjecture
      } else {
        goldbachWeakConjecture(inputNumbers, primeNumbers, &addends,
                               inputNumbersIndex, addendsIndex, sumsCount,
                               addendsCount);
      }
      array_int64_t_destroy(&addends);
    }
  } else {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

// Returns largest number from an array.
int64_t getLargestNumber(array_int64_t_t* inputNumbers) {
  int64_t largestInputNumber = 0;
  assert(inputNumbers);
  for (int index = 0; index < (int)inputNumbers->count; index++) {
    if ((llabs(inputNumbers->elements[index]) > largestInputNumber) &&
        (llabs(inputNumbers->elements[index] <= (9223372036854775807)))) {
      largestInputNumber = llabs(inputNumbers->elements[index]);
    }
  }
  return largestInputNumber;
}

// Calculates Goldbachs's strong conjecture sums
int goldbachStrongConjecture(array_int64_t_t* inputNumbers,
                             array_int64_t_t* primeNumbers,
                             array_int64_t_t* addends, int inputNumbersIndex,
                             int addendsIndex, int sumsCount,
                             int addendsCount) {
  // calculate every possible prime sum to find the goldbachs
  // combinations
  assert(inputNumbers);
  assert(primeNumbers);
  assert(addends);
  for (int64_t addend1 = 0; addend1 < (int)primeNumbers->count; addend1++) {
    for (int64_t addend2 = addend1; addend2 < (int)primeNumbers->count;
         addend2++) {
      // check if the sum of addends is equal to the inputNumber.
      if (primeNumbers->elements[addend1] != 0 &&
          primeNumbers->elements[addend2] != 0) {
        if ((primeNumbers->elements[addend1] +
             primeNumbers->elements[addend2]) ==
            llabs(inputNumbers->elements[inputNumbersIndex])) {
          if (inputNumbers->elements[inputNumbersIndex] < 0) {
            array_int64_t_append(addends, primeNumbers->elements[addend1]);
            array_int64_t_append(addends, primeNumbers->elements[addend2]);
            addendsIndex += 2;
          }
          sumsCount++;
        }
      }
    }
  }
  // printing.
  if (printGoldbachStrongConjecture(addends, inputNumbers, sumsCount,
                                    addendsIndex, addendsCount,
                                    inputNumbersIndex) == EXIT_FAILURE) {
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

// Calculates Goldbachs's weak conjecture sums
int goldbachWeakConjecture(array_int64_t_t* inputNumbers,
                           array_int64_t_t* primeNumbers,
                           array_int64_t_t* addends, int inputNumbersIndex,
                           int addendsIndex, int sumsCount, int addendsCount) {
  // calculate every possible prime sum to find the goldbachs
  // combinations
  assert(inputNumbers);
  assert(primeNumbers);
  assert(addends);
  for (int64_t addend1 = 0; addend1 < (int)primeNumbers->count; addend1++) {
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
              array_int64_t_append(addends, primeNumbers->elements[addend1]);
              array_int64_t_append(addends, primeNumbers->elements[addend2]);
              array_int64_t_append(addends, primeNumbers->elements[addend3]);
              addendsIndex += 3;
            }
            sumsCount++;
          }
        }
      }
    }
  }
  // printing.
  if (printGoldbachWeakConjecture(addends, inputNumbers, sumsCount,
                                  addendsIndex, addendsCount,
                                  inputNumbersIndex) == EXIT_FAILURE) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
