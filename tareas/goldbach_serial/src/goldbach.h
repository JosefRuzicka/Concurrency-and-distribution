// Copyright 2021 Josef Ruzicka <josef.ruzicka@ucr.ac.cr> CC-BY-4
// Outputs the prime numbers that sum the user-given numbers.
// 17/5/2021

#ifndef GOLDBACH_H
#define GOLDBACH_H

// #include <errno.h>
// #include <pthread.h>
#include <stdint.h>
#include <stdio.h>

#include "array_int64_t.h"
// #include <unistd.h>

// Method declaration:

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
int getInputNumbers(FILE* file, array_int64_t_t* inputNumbers);

/**
 * @brief Returns largest number from an array.
 * @details
 *  @code
 *    int64_t* inputNumbers = {1, 2, 3, 4, 5};
 *    int64_t* largestNumber = getLargestNumber(&inputNumbers);
 *  \endcode
 * @param inputNumbers: The number array of int64_t.
 */
int64_t getLargestNumber(array_int64_t_t* inputNumbers);

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
                        int64_t largestInputNumber);

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
                       array_int64_t_t* primeNumbers);

#endif  // GOLDBACH_H
