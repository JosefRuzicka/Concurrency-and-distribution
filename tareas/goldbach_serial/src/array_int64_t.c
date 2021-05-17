// Copyright 2021 Josef Ruzicka <josef.ruzicka@ucr.ac.cr> CC-BY-4
// Handles dynamic arrays of type int64_t.
// This code was adapted from the dynamic double array programed by
// Jeisson Hidalgo during a C workshop.
// 17/5/2021

#include "array_int64_t.h"

#include <assert.h>
#include <stdlib.h>

int array_int64_t_increase_capacity(array_int64_t_t* array);

int array_int64_t_init(array_int64_t_t* array) {
  assert(array);
  array->capacity = 0;
  array->count = 0;
  array->elements = NULL;
  return EXIT_SUCCESS;
}

void array_int64_t_destroy(array_int64_t_t* array) {
  assert(array);
  array->capacity = 0;
  array->count = 0;
  free(array->elements);
}

int array_int64_t_append(array_int64_t_t* array, int64_t element) {
  assert(array);
  if (array->count == array->capacity) {
    if (array_int64_t_increase_capacity(array) != EXIT_SUCCESS) {
      return EXIT_FAILURE;
    }
  }
  array->elements[array->count++] = element;
  return EXIT_SUCCESS;
}

int array_int64_t_increase_capacity(array_int64_t_t* array) {
  size_t new_capacity = 10 * (array->capacity ? array->capacity : 1);
  int64_t* new_elements =
      (int64_t*)realloc(array->elements, new_capacity * sizeof(int64_t));
  if (new_elements) {
    array->capacity = new_capacity;
    array->elements = new_elements;
    return EXIT_SUCCESS;
  } else {
    return EXIT_FAILURE;
  }
}
