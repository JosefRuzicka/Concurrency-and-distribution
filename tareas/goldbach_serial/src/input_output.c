// Copyright 2021 Josef Ruzicka <josef.ruzicka@ucr.ac.cr> CC-BY-4
// Outputs the prime numbers that sum the user-given numbers.
// 17/5/2021

#include "input_output.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "array_int64_t.h"

// Ask user for numbers and stores them in dynamic memory.
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

// Prints Goldbach's weak conjecture sums
int printGoldbachStrongConjecture(array_int64_t_t* addends,
                                  array_int64_t_t* inputNumbers, int sumsCount,
                                  int addendsIndex, int addendsCount,
                                  int inputNumbersIndex) {
  assert(addends);
  assert(inputNumbers);
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
      printf("%ld", addends->elements[addendsIndex]);
      printf(" + ");
      printf("%ld", addends->elements[addendsIndex + 1]);
      addendsIndex += 2;
    }
  }
  printf("\n");
  return EXIT_SUCCESS;
}

// Prints Goldbach's weak conjecture sums
int printGoldbachWeakConjecture(array_int64_t_t* addends,
                                array_int64_t_t* inputNumbers, int sumsCount,
                                int addendsIndex, int addendsCount,
                                int inputNumbersIndex) {
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
      printf("%ld", addends->elements[addendsIndex]);
      printf(" + ");
      printf("%ld", addends->elements[addendsIndex + 1]);
      printf(" + ");
      printf("%ld", addends->elements[addendsIndex + 2]);
      addendsIndex += 3;
    }
  }
  printf("\n");
  return EXIT_SUCCESS;
}
