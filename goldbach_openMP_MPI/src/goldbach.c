// Copyright 2021 Josef Ruzicka <josef.ruzicka@ucr.ac.cr> CC-BY-4
// Calculates the goldbach Sums of the user-input numbers.
// 17/5/2021
#include "goldbach.h"

#include <assert.h>
#include <math.h>
#include <omp.h>
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
                       array_int64_t_t* primeNumbers, int myRank,
                       int processCount) {
  // --------------------------ASSIGNMENT 4-------
  array_int64_t_t separatedInputNumbers;
  array_int64_t_init(&separatedInputNumbers /*[myRank]*/);

  // get range of input numbers to process.
  int myInputNumbersStart = myRank * (inputNumbers->count / processCount) +
                            fmin(myRank, (inputNumbers->count % processCount));
  int myInputNumbersFinish =
      (myRank + 1) * (inputNumbers->count / processCount) +
      fmin((myRank + 1), (inputNumbers->count % processCount));

  for (int inputNumber = myInputNumbersStart;
       inputNumber < myInputNumbersFinish; inputNumber++) {
    array_int64_t_append(&separatedInputNumbers /*[myRank]*/,
                         inputNumbers->elements[inputNumber]);
  }

  int64_t sumsCount = 0;
  int64_t addendsIndex = 0;
  int64_t addendsCount = 0;
  int64_t modulo = 0;
  // go through every input number.
  if (inputNumbers && primeNumbers) {
    for (int64_t inputNumbersIndex = 0;
         inputNumbersIndex < (int)separatedInputNumbers.count;
         inputNumbersIndex++) {
      int64_t absValueInputNumber =
          llabs(separatedInputNumbers.elements[inputNumbersIndex]);
      array_int64_t_t addends;
      array_int64_t_init(&addends);
      addendsIndex = 0;
      printf("%ld:", (separatedInputNumbers.elements[inputNumbersIndex]));
      sumsCount = 0;
      modulo = (absValueInputNumber % 2);
      // check if number is in range
      if (absValueInputNumber <= 5 ||
          absValueInputNumber > (9223372036854775807)) {
        printf(" NA\n");

        // Goldbachs Strong Conjecture
      } else if (modulo == 0) {
        goldbachStrongConjecture(&separatedInputNumbers, primeNumbers, &addends,
                                 inputNumbersIndex, addendsIndex, sumsCount,
                                 addendsCount);
        // Goldbachs Weak Conjecture
      } else {
        goldbachWeakConjecture(&separatedInputNumbers, primeNumbers, &addends,
                               inputNumbersIndex, addendsIndex, sumsCount,
                               addendsCount);
      }
      array_int64_t_destroy(&addends);
    }
    array_int64_t_destroy(&separatedInputNumbers);
    // MPI_Finalize();
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
                             array_int64_t_t* addends,
                             int64_t inputNumbersIndex, int64_t addendsIndex,
                             int64_t sumsCount, int64_t addendsCount) {
  // calculate every possible prime sum to find the goldbachs
  // combinations
  assert(inputNumbers);
  assert(primeNumbers);
  assert(addends);
  int64_t absValueInputNumber =
      llabs(inputNumbers->elements[inputNumbersIndex]);
  int64_t maxAddend = 0;

  // because omp doesnt support this method in the for loop
  for (int64_t primeNumbersIndex = 0;
       primeNumbers->elements[primeNumbersIndex] <=
       ((absValueInputNumber / 2) + 1);
       primeNumbersIndex++) {
    maxAddend++;
  }

  // for printing in order
  bool appendedAddends[maxAddend];
  appendedAddends[0] = 1;
  for (int64_t index = 1; index < maxAddend; index++) {
    appendedAddends[index] = 0;
  }
#pragma omp parallel for default(none) schedule(dynamic)                       \
    shared(primeNumbers, absValueInputNumber, inputNumbers, inputNumbersIndex, \
           addends, addendsIndex, sumsCount, maxAddend, appendedAddends)
  for (int64_t addend1 = 0; addend1 < maxAddend; addend1++) {
    for (int64_t addend2 = addend1;
         primeNumbers->elements[addend2] <= absValueInputNumber; addend2++) {
      // check if the sum of addends is equal to the inputNumber.
      if ((primeNumbers->elements[addend1] + primeNumbers->elements[addend2]) ==
          absValueInputNumber) {
        if (inputNumbers->elements[inputNumbersIndex] < 0) {
          // printf("%ld\n", appendedAddends);
          while (appendedAddends[addend1] == 0) {
          }
#pragma omp critical
          array_int64_t_append(addends, primeNumbers->elements[addend1]);
          array_int64_t_append(addends, primeNumbers->elements[addend2]);
          addendsIndex += 2;
        }
#pragma omp critical
        sumsCount++;
      }
    }
    // wait to print
    while (appendedAddends[addend1] == 0) {
    }
    if (addend1 <= maxAddend) {
      appendedAddends[addend1 + 1] = 1;
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
                           array_int64_t_t* addends, int64_t inputNumbersIndex,
                           int64_t addendsIndex, int64_t sumsCount,
                           int64_t addendsCount) {
  // calculate every possible prime sum to find the goldbachs
  // combinations
  assert(inputNumbers);
  assert(primeNumbers);
  assert(addends);
  int64_t absValueInputNumber =
      llabs(inputNumbers->elements[inputNumbersIndex]);

  int64_t maxAddend = 1;
  for (int64_t primeNumbersIndex = 0;
       primeNumbers->elements[primeNumbersIndex] <=
       ((absValueInputNumber / 2) + 1);
       primeNumbersIndex++) {
    maxAddend++;
  }

  // for printing in order
  bool appendedAddends[maxAddend];
  appendedAddends[0] = 1;
  for (int64_t index = 1; index < maxAddend; index++) {
    appendedAddends[index] = 0;
  }

#pragma omp parallel for default(none) schedule(dynamic)                       \
    shared(primeNumbers, absValueInputNumber, inputNumbers, inputNumbersIndex, \
           addends, addendsIndex, sumsCount, maxAddend, appendedAddends)
  for (int64_t addend1 = 0; addend1 <= maxAddend; addend1++) {
    for (int64_t addend2 = addend1;
         (addend2 < (int64_t)primeNumbers->count) &&
         (primeNumbers->elements[addend2] < absValueInputNumber);
         addend2++) {
      for (int64_t addend3 = addend2;
           (addend3 < (int64_t)primeNumbers->count) &&
           (primeNumbers->elements[addend3] < absValueInputNumber);
           addend3++) {
        // check if the sum of addends is equal to the inputNumber.
        if ((primeNumbers->elements[addend1] + primeNumbers->elements[addend2] +
             primeNumbers->elements[addend3]) == absValueInputNumber) {
          if (inputNumbers->elements[inputNumbersIndex] < 0) {
            while (appendedAddends[addend1] == 0) {
            }
#pragma omp critical
            array_int64_t_append(addends, primeNumbers->elements[addend1]);
            array_int64_t_append(addends, primeNumbers->elements[addend2]);
            array_int64_t_append(addends, primeNumbers->elements[addend3]);
            addendsIndex += 3;
          }
#pragma omp critical
          sumsCount++;
        }
        //}
      }
    }
    // wait to print
    while (appendedAddends[addend1] == 0) {
    }
    if (addend1 <= maxAddend) {
      appendedAddends[addend1 + 1] = 1;
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
