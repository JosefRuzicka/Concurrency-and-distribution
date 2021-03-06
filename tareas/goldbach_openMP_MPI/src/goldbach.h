// Copyright 2021 Josef Ruzicka <josef.ruzicka@ucr.ac.cr> CC-BY-4
// Calculates the goldbach Sums of the user-input numbers.
// 17/5/2021

#ifndef GOLDBACH_H
#define GOLDBACH_H

#include <stdint.h>
#include <stdio.h>

#include "array_int64_t.h"

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
 * @brief calculates the goldbach sums that add up to the input numbers.
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
                       array_int64_t_t* primeNumbers, int myRank,
                       int processCount);

/**
 * @brief Calculates Goldbach's strong conjecture sums.
 * @details
 *  @code
 *    array_int64_t_t inputNumbers;
 *    array_int64_t_init(&inputNumbers);
 *    array_int64_t_t addends;
 *    array_int64_t_init(&addends);
 *    int sumsCount = 2;
 *    int addendsCount = 4;
 *    int addendsIndex = 0;
 *    int inputNumbersIndex;
 *    goldbachStrongConjecture(array_int64_t_t* addends,
 *                                array_int64_t_t* inputNumbers, int sumsCount,
 *                                int addendsIndex, int addendsCount,
 *                                int inputNumbersIndex);
 *  \endcode
 * @param addends: The array of int_64_t that will contain the addends to sum
 * the numbers in question.
 * @param inputNumbers: The array of int_64_t that contains the numbers in
 * question.
 * @param sumsCount: The counter to the amount of sums to be printed.
 * @param addendsIndex: The position tracking of the addends in addends.
 * @param addendsCount: The counter to the amount of addends to be printed.
 * @param inputNumbersIndex: The position tracking of the addend to be printed
 * in addends.
 */
int goldbachStrongConjecture(array_int64_t_t* inputNumbers,
                             array_int64_t_t* primeNumbers,
                             array_int64_t_t* addends,
                             int64_t inputNumbersIndex, int64_t addendsIndex,
                             int64_t sumsCount, int64_t addendsCount);

/**
 * @brief Calculates Goldbach's weak conjecture sums.
 * @details
 *  @code
 *    array_int64_t_t inputNumbers;
 *    array_int64_t_init(&inputNumbers);
 *    array_int64_t_t addends;
 *    array_int64_t_init(&addends);
 *    int sumsCount = 2;
 *    int addendsCount = 4;
 *    int addendsIndex = 0;
 *    int inputNumbersIndex;
 *    goldbachWeakConjecture(array_int64_t_t* addends,
 *                                array_int64_t_t* inputNumbers, int sumsCount,
 *                                int addendsIndex, int addendsCount,
 *                                int inputNumbersIndex);
 *  \endcode
 * @param addends: The array of int_64_t that will contain the addends to sum
 * the numbers in question.
 * @param inputNumbers: The array of int_64_t that contains the numbers in
 * question.
 * @param sumsCount: The counter to the amount of sums to be printed.
 * @param addendsIndex: The position tracking of the addends in addends.
 * @param addendsCount: The counter to the amount of addends to be printed.
 * @param inputNumbersIndex: The position tracking of the addend to be printed
 * in addends.
 */
int goldbachWeakConjecture(array_int64_t_t* inputNumbers,
                           array_int64_t_t* primeNumbers,
                           array_int64_t_t* addends, int64_t inputNumbersIndex,
                           int64_t addendsIndex, int64_t sumsCount,
                           int64_t addendsCount);

#endif  // GOLDBACH_H
