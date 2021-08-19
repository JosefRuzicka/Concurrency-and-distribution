// Copyright 2021 Josef Ruzicka, Samantha Romero, Carlos Solorzano. Universidad
// de Costa Rica.

#include <mpi.h>

#include <chrono>

#include "Wizard.h"

int main(int argc, char* argv[]) {
  MPI_Init(&argc, &argv);

  int myRank = -1;
  MPI_Comm_rank(MPI_COMM_WORLD, &myRank);

  int processCount = -1;
  MPI_Comm_size(MPI_COMM_WORLD, &processCount);

  char hostname[MPI_MAX_PROCESSOR_NAME];

  int hostname_length = -1;
  MPI_Get_processor_name(hostname, &hostname_length);

  printf("Process %d of %d en la compu %s \n", myRank, processCount, hostname);

  std::chrono::steady_clock::time_point begin =
      std::chrono::steady_clock::now();

  Wizard merlin(myRank, processCount);

  merlin.startWorking(argc, argv);
  std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

  std::cout
      << "Proceso " << myRank << " Time difference = "
      << std::chrono::duration_cast<std::chrono::seconds>(end - begin).count()
      << "[s]" << std::endl;

  MPI_Finalize();
}
