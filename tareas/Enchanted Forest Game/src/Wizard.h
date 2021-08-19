/**
 * Wizard class. Controller class for the forest simulations program.
 * Programmed by Josef Ruzicka, Samantha Romero and Carlos Solorzano.
 */

#ifndef _WIZARD_H
#define _WIZARD_H
#include <iostream>
#include <vector>

#include "SpellSimulator.h"
#include "WorkOrder.h"
class Wizard {
 public:
  /**
   * @param argc
   * @param argv[]
   */
  void startWorking(int argc, char* argv[]);
  Wizard(int my_rank, int process_count);

 private:
  // vector of input maps.
  std::vector<WorkOrder> workOrders;
  std::string jobFileName;
  SpellSimulator staffOfAvalon;
  // route to the folder containing the job and map files.
  std::string defaultRoute;
  size_t myRank;
  size_t processCount;
  // starting map of a process.
  size_t leftLimit;
  // finishing map of a process.
  size_t rightLimit;

  void calculateMapsRange();

  /**
   * @brief: calculate staring map for a process to work on.
   * @param myRank: current process.
   * @param workUnits: amount of maps.
   * @param workers: amount of processes.
   */
  size_t getStart(size_t myRank, size_t workUnits, size_t workers);

  /**
   * @brief: calculate finishing map for a process to work on.
   * @param myRank: current process.
   * @param workUnits: amount of maps.
   * @param workers: amount of processes.
   */
  size_t getFinish(size_t processCount, size_t workUnits, size_t workers);
  /**
   * @brief: stores the input maps into the workOrders vector.
   */
  int extractWorkOrders();

  /**
   * @brief: checks which maps are suitable to be worked on.
   */
  int verifyAllMaps();

  /**
   * @brief: checks which job was asked for and which route must be used in
   * order to find it.
   * @param argc
   * @param argv[]
   */
  int analizeArguments(int argc, char* argv[]);

  /**
   * @brief: checks if the map is correctly formatted for processing.
   * @param fileName
   */
  int verifyMap(const std::string& fileName);

  /**
   * @brief: run simulations.
   */
  void processWorkOrders();
};

#endif  //_WIZARD_H