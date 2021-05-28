// Copyright 2021 Josef Ruzicka <josef.ruzicka@ucr.ac.cr> CC-BY-4
// Outputs the prime numbers that sum the user-given numbers.
// 17/5/2021

#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H

#include <stdint.h>
#include <stdio.h>

#include "array_int64_t.h"

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
 * @brief Prints de Goldbach's strong conjecture sums.
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
 *    printGoldbachStrongConjecture(array_int64_t_t* addends,
 *                                array_int64_t_t* inputNumbers, int sumsCount,
 *                                int addendsIndex, int addendsCount,
 *                                int inputNumbersIndex);
 *  \endcode
 * @param addends: the addends that are equal to the number in quiestion when
 * summed.
 * @param inputNumbers: The array of int_64_t that contains the numbers in
 * question.
 * @param sumsCount: The amount of sums to be printed.
 * @param addendsIndex: The position of the addend to be printed in addends.
 * @param addendsCount: The amount of addends to be printed.
 * @param inputNumbersIndex: The position of the addend to be printed in
 * addends.
 */
int printGoldbachStrongConjecture(array_int64_t_t* addends,
                                  array_int64_t_t* inputNumbers, int sumsCount,
                                  int addendsIndex, int addendsCount,
                                  int inputNumbersIndex);

/**
 * @brief Prints de Goldbach's weak conjecture sums.
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
 *    printGoldbachStrongConjecture(array_int64_t_t* addends,
 *                                array_int64_t_t* inputNumbers, int sumsCount,
 *                                int addendsIndex, int addendsCount,
 *                                int inputNumbersIndex);
 *  \endcode
 * @param addends: the addends that are equal to the number in quiestion when
 * summed.
 * @param inputNumbers: The array of int_64_t that contains the numbers in
 * question.
 * @param sumsCount: The amount of sums to be printed.
 * @param addendsIndex: The position of the addend to be printed in addends.
 * @param addendsCount: The amount of addends to be printed.
 * @param inputNumbersIndex: The position of the addend to be printed in
 * addends.
 */
int printGoldbachWeakConjecture(array_int64_t_t* addends,
                                array_int64_t_t* inputNumbers, int sumsCount,
                                int addendsIndex, int addendsCount,
                                int inputNumbersIndex);

/**
 * @brief Prints "NA" to indicates the value is out of range.
 * @details
 *  @code
 *    array_int64_t_t inputNumbers;
 *    array_int64_t_init(&inputNumbers);
 *    array_int64_t_append(&inputNumbers, 2);
 *    printOutOfRange(&inputNumbers, 0);
 *  \endcode
 * @param inputNumbers: The array accessed to print its content and the out of
 * range message.
 * @param inputNumbersIndex: The index to the element of array to be printed.
 */
void printOutOfRange(array_int64_t_t* inputNumbers, int inputNumbersIndex);

#endif  // INPUT_OUTPUT_H
