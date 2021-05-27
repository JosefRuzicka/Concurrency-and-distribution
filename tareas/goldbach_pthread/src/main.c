// Copyright 2021 Josef Ruzicka <josef.ruzicka@ucr.ac.cr> CC-BY-4
// Main file for the goldbach Assignment.
// 24/5/2021

#include <assert.h>
#include <errno.h>
#include <math.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "array_int64_t.h"
#include "goldbach.h"
#include "input_output.h"

typedef struct {
  size_t thread_count;
  size_t position;
  sem_t* can_print;
  sem_t mutex;
  array_int64_t_t inputNumbers;
  array_int64_t_t primeNumbers;
} shared_data_t;

typedef struct {
  size_t thread_number;
  size_t position;
  shared_data_t* shared_data;
} private_data_t;

int create_threads(shared_data_t* shared_data);
void* run(void* data);

/**
 * @brief Main method to calculate Goldbachs conjecture numbers.
 */
int main(int argc, char* argv[]) {
  //-------------- old main ------------
  FILE* input = stdin;
  // ask user for numbers.
  // array_int64_t_t inputNumbers;
  // array_int64_t_init(&inputNumbers);
  // getInputNumbers(input, &inputNumbers);

  // get the largest number from input
  // int64_t largestInputNumber = getLargestNumber(&inputNumbers);

  // get the prime numbers with sieve of Eratosthenes.
  // array_int64_t_t primeNumbers;
  // array_int64_t_init(&primeNumbers);
  // sieveOfEratosthenes(&primeNumbers, largestInputNumber);
  //------------------------------------
  // ------------- TAREA 2 -------------
  // ------------ Signaling ------------

  // Taken and adapted from the code shown in class by prof. Jeisson Hidalgo &
  // prof. Allan Berrocal
  int error = EXIT_SUCCESS;

  shared_data_t* shared_data = (shared_data_t*)calloc(1, sizeof(shared_data_t));

  if (shared_data) {
    //------- main code --------
    array_int64_t_init(&shared_data->inputNumbers);
    getInputNumbers(input, &shared_data->inputNumbers);
    int64_t largestInputNumber = getLargestNumber(&shared_data->inputNumbers);
    array_int64_t_init(&shared_data->primeNumbers);
    sieveOfEratosthenes(&shared_data->primeNumbers, largestInputNumber);
    //--------------------------
    shared_data->position = 0;
    shared_data->thread_count = sysconf(_SC_NPROCESSORS_ONLN);
    if (argc == 2) {
      if (sscanf(argv[1], "%zu", &shared_data->thread_count) != 1 || errno) {
        fprintf(stderr, "error: invalid thread count\n");
        error = 1;
      }
    }
    if (error == EXIT_SUCCESS) {
      shared_data->can_print =
          (sem_t*)calloc(shared_data->thread_count, sizeof(sem_t));
      if (shared_data->can_print) {
        create_threads(shared_data);
        free(shared_data->can_print);
      } else {
        fprintf(stderr, "error: could not allocate semaphores\n");
        error = 3;
      }
      array_int64_t_destroy(&shared_data->inputNumbers);
      array_int64_t_destroy(&shared_data->primeNumbers);
      free(shared_data);
    } else {
      fprintf(stderr, "error: could not allocate shared memory\n");
      error = 2;
    }
  }
  // ------------- FIN TAREA 2 -------------
  // deallocation of memory.
  // array_int64_t_destroy(&inputNumbers);
  // array_int64_t_destroy(&primeNumbers);
  return error;
}

// while shared->position = 0 inputNumbers->count
// lock
// private->data position = shared->position
// shared->position++;
// unlock
// (calcular goldbach(private->position))
// -----------------------------------

// Taken and adapted from the code shown in class by prof. Jeisson Hidalgo &
// prof. Allan Berrocal
int create_threads(shared_data_t* shared_data) {
  assert(shared_data);
  int error = EXIT_SUCCESS;
  // create mutex
  error = sem_init(&shared_data->mutex, /*pshared*/ 0,
                   /*value*/ 1);
  if (error == EXIT_SUCCESS) {
    // create threads
    pthread_t* threads =
        (pthread_t*)calloc(shared_data->thread_count, sizeof(pthread_t));
    private_data_t* private_data = (private_data_t*)calloc(
        shared_data->thread_count, sizeof(private_data_t));
    if (threads && private_data) {
      for (size_t index = 0; index < shared_data->thread_count; ++index) {
        private_data[index].thread_number = index;
        private_data[index].shared_data = shared_data;

        error = sem_init(&shared_data->can_print[index], /*pshared*/ 0,
                         /*value*/ !index);

        if (error == EXIT_SUCCESS) {
          if (pthread_create(&threads[index], /*attr*/ NULL, run,
                             &private_data[index]) == EXIT_SUCCESS) {
          } else {
            fprintf(stderr, "error: could not create thread %zu\n", index);
            error = 21;
            shared_data->thread_count = index;
            break;
          }
        } else {
          fprintf(stderr, "error: could not init semaphore %zu\n", index);
          error = 22;
          shared_data->thread_count = index;
          break;
        }
      }

      // main thread's task
      //--------------------
      // printf("Hello from main thread\n");

      //--------------------

      for (size_t index = 0; index < shared_data->thread_count; ++index) {
        pthread_join(threads[index], /*value_ptr*/ NULL);
        sem_destroy(&shared_data->can_print[index]);
      }
      free(threads);
      free(private_data);
    } else {
      fprintf(stderr, "error: could not allocate memory for %zu threads\n",
              shared_data->thread_count);
      error = 22;
    }
  } else {
    fprintf(stderr, "error: could not allocate memory for mutex\n");
    error = 23;
  }

  return error;
}

// Taken and adapted from the code shown in class by prof. Jeisson Hidalgo &
// prof. Allan Berrocal
void* run(void* data) {
  const private_data_t* private_data = (private_data_t*)data;
  shared_data_t* shared_data = private_data->shared_data;
  // const size_t my_thread_id = private_data->thread_number;
  const size_t thread_count = shared_data->thread_count;
  size_t my_position = 0;

  // Thread's task
  // Cada hilo toma un numero del input para calcular sus sumas.
  while (shared_data->position < shared_data->inputNumbers.count) {
    sem_wait(&shared_data->mutex);
    my_position = shared_data->position;
    shared_data->position++;
    // printf("Hello from thread %zu of %zu\n", my_thread_id, thread_count);
    sem_post(&shared_data->mutex);
    // printf("inputNumbersCount = %d and my position = %d \n",
    //       shared_data->inputNumbers.count, my_position);
    if (my_position < shared_data->inputNumbers.count) {
      goldbachConjecture(
          &shared_data->inputNumbers, &shared_data->primeNumbers, my_position,
          &shared_data->can_print[my_position],
          &shared_data->can_print[(my_position + 1) % thread_count]);
    }
  }
  // sem_wait(&shared_data->can_print[my_thread_id]);
  // printf("Hello from thread %zu of %zu\n", my_thread_id, thread_count);
  // sem_post(&shared_data->can_print[(my_thread_id + 1) % thread_count]);

  return NULL;
}
