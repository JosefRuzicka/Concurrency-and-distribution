// Copyright 2021 Josef Ruzicka <josef.ruzicka@ucr.ac.cr> CC-BY-4
// Handles dynamic arrays of type int64_t.
// This code was adapted from the dynamic double array programed by
// Jeisson Hidalgo during a C workshop.
// 8/5/2021

#ifndef ARRAY_INT64_T_H
#define ARRAY_INT64_T_H

#include <stddef.h>
#include <stdint.h>

typedef struct {
  size_t capacity;
  size_t count;
  int64_t* elements;
} array_int64_t_t;

int array_int64_t_init(array_int64_t_t* array);
void array_int64_t_destroy(array_int64_t_t* array);
int array_int64_t_append(array_int64_t_t* array, int64_t element);

#endif  // ARRAY_INT64_T_H
