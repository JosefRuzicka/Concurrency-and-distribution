// Copyright 2021 Josef Ruzicka <josef.ruzicka@ucr.ac.cr> CC-BY-4
// Main file for the goldbach Assignment.
// 17/5/2021

#include <math.h>
// #include <mpi/mpi.h>
#include <mpi.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "array_int64_t.h"
#include "goldbach.h"
#include "input_output.h"

/**
 * @brief Main method to calculate Goldbachs conjecture numbers.
 */
int main(int argc, char* argv[]) {
  MPI_Init(&argc, &argv);

  int myRank = -1;
  MPI_Comm_rank(MPI_COMM_WORLD, &myRank);

  int processCount = -1;
  MPI_Comm_size(MPI_COMM_WORLD, &processCount);

  char hostname[MPI_MAX_PROCESSOR_NAME];

  int hostname_length = -1;
  MPI_Get_processor_name(hostname, &hostname_length);

  // Time measuring. 1/2
  struct timespec start_time;
  clock_gettime(/*clk_id*/ CLOCK_MONOTONIC, &start_time);
  FILE* input = stdin;

  array_int64_t_t inputNumbers;
  array_int64_t_init(&inputNumbers);

  int inputNumbersCount = 0;
  if (myRank == 0) {
    getInputNumbers(input, &inputNumbers);
    inputNumbersCount = inputNumbers.count;
    int64_t receivedInputNumbers[inputNumbersCount];

    for (int index = 0; index < inputNumbersCount; index++) {
      receivedInputNumbers[index] = inputNumbers.elements[index];
    }
    for (int target = 1; target < processCount; ++target) {
      // Send value count to target
      if (MPI_Send(&inputNumbers.count, /*count*/ 1, MPI_INT, target,
                   /*tag*/ 0, MPI_COMM_WORLD) == MPI_SUCCESS) {
        // Send values to target
        if (MPI_Send(&receivedInputNumbers[0], /*count*/ inputNumbersCount,
                     MPI_LONG_LONG_INT, target,
                     /*tag*/ 0, MPI_COMM_WORLD) != MPI_SUCCESS) {
          printf("error: could not send values\n");
        }
      } else {
        printf("error: could not value count\n");
      }
    }
  } else {
    // Receive the value count from process 0
    int64_t* receivedInputNumbers = (int64_t*)calloc(10, sizeof(int64_t));
    int myCount = 0;
    if (MPI_Recv(&inputNumbersCount, /*capacity*/ 1, MPI_INT,
                 /*source*/ 0, /*tag*/ 0, MPI_COMM_WORLD,
                 MPI_STATUS_IGNORE) == MPI_SUCCESS) {
      myCount = inputNumbersCount;
      receivedInputNumbers =
          (int64_t*)realloc(receivedInputNumbers, myCount * sizeof(int64_t));
      // Receive values from process 0
      if (MPI_Recv(&receivedInputNumbers[0], /*capacity*/ myCount,
                   MPI_LONG_LONG_INT, /*source*/ 0,
                   /*tag*/ 0, MPI_COMM_WORLD,
                   MPI_STATUS_IGNORE) != MPI_SUCCESS) {
        printf("could not receive values\n");
      }
    } else {
      printf(": could not receive value count\n");
    }
    for (int index = 0; index < myCount; index++) {
      array_int64_t_append(&inputNumbers, receivedInputNumbers[index]);
    }
  }

  // get the largest number from input
  int64_t largestInputNumber = getLargestNumber(&inputNumbers);

  // get the prime numbers with sieve of Eratosthenes.
  array_int64_t_t primeNumbers;
  array_int64_t_init(&primeNumbers);
  sieveOfEratosthenes(&primeNumbers, largestInputNumber);

  goldbachConjecture(&inputNumbers, &primeNumbers, myRank, processCount);

  // deallocation of memory.
  array_int64_t_destroy(&inputNumbers);
  array_int64_t_destroy(&primeNumbers);

  // Time measuring. 2/2
  struct timespec finish_time;
  clock_gettime(/*clk_id*/ CLOCK_MONOTONIC, &finish_time);

  // Time measure printing.
  double elapsed = (finish_time.tv_sec - start_time.tv_sec) +
                   (finish_time.tv_nsec - start_time.tv_nsec) * 1e-9;
  fprintf(stderr, "execution time: %.9lfs\n", elapsed);

  printf("Proceso %d  Time difference = %.9lfs\n", myRank, elapsed);

  MPI_Finalize();

  return 0;
}
