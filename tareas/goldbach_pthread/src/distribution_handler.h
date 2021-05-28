// Copyright 2021 Josef Ruzicka <josef.ruzicka@ucr.ac.cr> CC-BY-4
// Distribution handler for the goldbach Assignment.
// 17/5/2021

#ifndef DISTRIBUTION_HANDLER_H
#define DISTRIBUTION_HANDLER_H

#include <semaphore.h>

#include "array_int64_t.h"

// shared data, may be accessed by all threads.
typedef struct {
  size_t thread_count;
  size_t position;
  sem_t* can_print;
  sem_t mutex;
  array_int64_t_t inputNumbers;
  array_int64_t_t primeNumbers;
} shared_data_t;

// private data, each thread has its own private data, and its accessable only
// by itself.
typedef struct {
  size_t thread_number;
  size_t position;
  shared_data_t* shared_data;
} private_data_t;

/**
 * @brief Creates threads.
 * @details
 *  @code
 *    shared_data_t* shared_data = (shared_data_t*)calloc(1,
 *    sizeof(shared_data_t));
 *    create_threads(shared_data);
 *  \endcode
 * @param array: The array to be initialized.
 */
int create_threads(shared_data_t* shared_data);

/**
 * @brief Thread task.
 * @details
 *  @code
 *    pthread_t* threads =
 *    (pthread_t*)calloc(shared_data->thread_count, sizeof(pthread_t));
 *    pthread_create(&threads[index],  NULL, run,
 *                           &private_data[index]);
 *  \endcode
 * @param data: Used to create the threads private data.
 */
void* run(void* data);

/**
 * @brief Main method to calculate Goldbachs conjecture numbers distributedly.
 * @param argc: argument count.
 * @param argv: argument values.
 */
int goldbachConjectureDistributed(int argc, char* argv[]);

#endif  // DISTRIBUTION_HANDLER_H
