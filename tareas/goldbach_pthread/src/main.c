// Copyright 2021 Josef Ruzicka <josef.ruzicka@ucr.ac.cr> CC-BY-4
// Main program for calculating Goldbach's Conjecture Sums distributedly.
// 28/5/2021

#include "distribution_handler.h"

/**
 * @brief Main method to calculate Goldbachs conjecture numbers.
 */
int main(int argc, char* argv[]) {
  int error = goldbachConjectureDistributed(argc, argv);
  return error;
}
