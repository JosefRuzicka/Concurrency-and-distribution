// Copyright 2021 Josef Ruzicka <josef.ruzicka@ucr.ac.cr> CC-BY-4
// Main file for the goldbach Assignment.
// 24/5/2021

#include <assert.h>
#include <errno.h>
#include <math.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
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
          (sem_t*)calloc(shared_data->inputNumbers.count, sizeof(sem_t));
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
  return error;
}

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
      // create semaphores to print the input numbers in order and thread safe
      for (size_t index = 0; index < shared_data->inputNumbers.count; index++) {
        error = sem_init(&shared_data->can_print[index], /*pshared*/ 0,
                         /*value*/ !index);
      }

      for (size_t index = 0; index < shared_data->thread_count; ++index) {
        private_data[index].thread_number = index;
        private_data[index].shared_data = shared_data;

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
  size_t my_position = 0;
  bool finished = false;

  // Thread's task
  // Cada hilo toma un numero del input para calcular sus sumas.
  // while (shared_data->position < shared_data->inputNumbers.count) {
  while (!finished) {
    sem_wait(&shared_data->mutex);
    if (shared_data->position < shared_data->inputNumbers.count) {
      my_position = shared_data->position;
      shared_data->position++;
      sem_post(&shared_data->mutex);
      goldbachConjecture(
          &shared_data->inputNumbers, &shared_data->primeNumbers, my_position,
          &shared_data->can_print[my_position],
          &shared_data->can_print[(my_position + 1) %
                                  shared_data->inputNumbers.count]);
    } else {
      finished = true;
      sem_post(&shared_data->mutex);
    }
  }
  return NULL;
}
