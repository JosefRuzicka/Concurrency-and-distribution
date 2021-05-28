// Copyright 2021 Josef Ruzicka <josef.ruzicka@ucr.ac.cr> CC-BY-4
// Handles dynamic arrays of type int64_t.
// This code was adapted from the dynamic double array programed by
// Jeisson Hidalgo during a C workshop.
// 17/5/2021

#ifndef ARRAY_INT64_T_H
#define ARRAY_INT64_T_H

#include <stddef.h>
#include <stdint.h>

// the data of the array, its size, its elements and their amount.
typedef struct {
  size_t capacity;
  size_t count;
  int64_t* elements;
} array_int64_t_t;

/**
 * @brief Initializes array.
 * @details
 *  @code
 *    array_int64_t_t array;
 *    array_int64_t_init(&array);
 *  \endcode
 * @param array: The array to be initialized.
 */
int array_int64_t_init(array_int64_t_t* array);

/**
 * @brief Frees the memory used by array.
 * @details
 *  @code
 *    array_int64_t_t array;
 *    array_int64_t_init(&array);
 *    array_int64_t_destroy(&array);
 *  \endcode
 * @param array: The array to be initialized.
 */
void array_int64_t_destroy(array_int64_t_t* array);

/**
 * @brief Adds an element to the array.
 * @details
 *  @code
 *    array_int64_t_t array;
 *    array_int64_t_init(&array);
 *    array_int64_t_append(&array, 1);
 *  \endcode
 * @param array: The array on which the element is to be added.
 * @param element: The element to be added.
 */
int array_int64_t_append(array_int64_t_t* array, int64_t element);

#endif  // ARRAY_INT64_T_H
