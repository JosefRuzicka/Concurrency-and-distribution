// Copyright 2021 Josef Ruzicka <josef.ruzicka@ucr.ac.cr> CC-BY-4
// Main file for the goldbach Assignment.
// 17/5/2021

// #include <errno.h>
// #include <pthread.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array_int64_t.h"
#include "goldbach.h"

/**
 * @brief Main method to calculate Goldbachs conjecture numbers.
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
