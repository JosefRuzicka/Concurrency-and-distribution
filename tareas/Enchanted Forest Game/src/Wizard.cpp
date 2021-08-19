// Copyright 2021 Josef Ruzicka, Samantha Romero, Carlos Solorzano. Universidad
// de Costa Rica.

#include "Wizard.h"

#include <omp.h>

#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "SpellSimulator.h"
#include "WorkOrder.h"
using std::cout;
using std::endl;
using std::string;

void Wizard::startWorking(int argc, char* argv[]) {
  this->defaultRoute = argv[2];
  string name = reinterpret_cast<char*>(argv[1]);

  this->jobFileName.append(this->defaultRoute);

  this->jobFileName.append(name);

  this->calculateMapsRange();
  this->processWorkOrders();
}

int Wizard::extractWorkOrders() {
  std::ifstream fileName;
  string line;
  string subLineNights;
  string subLineFileName;
  int night;
  bool printAllNights;

  fileName.open(this->jobFileName, std::ios::in);

  if (!(fileName.is_open())) {
    cout << "error opening file";
  }

  while (getline(fileName, line)) {
    printAllNights = true;

    subLineNights = line.substr(11);
    night = abs(atoi(subLineNights.c_str()));

    subLineFileName = line.substr(0, 10);
    if (line.substr(11, 1) == "-") {
      printAllNights = false;
    }
    WorkOrder order(night, subLineFileName, printAllNights);
    this->workOrders.push_back(order);
  }
  fileName.close();
  return EXIT_SUCCESS;
}

int Wizard::verifyAllMaps() {
  for (size_t mapIndex = 0; mapIndex < this->workOrders.size(); mapIndex++) {
    if (this->verifyMap(this->defaultRoute +
                        this->workOrders[mapIndex].getFileName()) ==
        EXIT_FAILURE) {
      this->workOrders[mapIndex].setIsValid(false);
      std::cout << "Invalid map line: " << mapIndex << "\n";
    }
  }
  return EXIT_SUCCESS;
}

int Wizard::verifyMap(const string& mapName) {
  std::ifstream file;
  size_t rows;
  size_t columns;
  string line;
  std::vector<string> tokens;

  file.open(mapName, std::ios::in);
  getline(file, line);

  std::stringstream stream(line);

  string token;

  while (getline(stream, token, ' ')) {
    tokens.push_back(token);
  }
  if (tokens.size() != 2) {
    std::cout << "Invalid map size (only need rows and columns) \n";
    return EXIT_FAILURE;
  }

  bool validSize = true;

  // Verify that size is correct
  for (size_t tokenIndex = 0; tokenIndex < tokens.size() && validSize;
       tokenIndex++) {
    token = tokens[tokenIndex];
    for (size_t index = 0; index < token.length() && validSize; index++) {
      if (!(token[index] <= '9' && token[index] >= '0')) {
        validSize = false;
      }
    }
  }
  if (!validSize) {
    std::cout << "Invalid map size  \n";
    return EXIT_FAILURE;
  }
  // Assign rows and columns
  rows = stoi(tokens[0]);
  columns = stoi(tokens[1]);

  size_t rowCount = 0;

  // Verify that all cells are valid
  while (getline(file, line)) {
    rowCount++;
    tokens.clear();
    // Verify that columns on map match expected quantity
    if (line.length() != columns) {
      std::cout << "Invalid matrix in row " << rowCount
                << " expected: " << columns << " found: " << tokens.size()
                << "\n";
      return EXIT_FAILURE;
    }
    for (char i : line) {
      if (i != 'a' && i != 'l' && i != '-') {
        std::cout << "Invalid cell on map\n";
        return EXIT_FAILURE;
      }
    }
  }
  file.close();

  // Verify that rows on map match expected quantity
  if (rowCount != rows) {
    std::cout << "Rows doesnt match:" << rows << " " << rowCount << '\n';
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

void Wizard::processWorkOrders() {
  std::ifstream file;
  std::ofstream outputFile;
  int rows;
  int columns;
  string line;
  std::vector<string> tokens;

  printf("Process %zu left: %zu, right: %zu, vectorSize:%zu \n", this->myRank,
         this->leftLimit, this->rightLimit, this->workOrders.size());

  for (size_t index = this->leftLimit; index < this->rightLimit; index++) {
    WorkOrder* workOrder = &this->workOrders[index];
    tokens.clear();
    file.open(this->defaultRoute + workOrder->getFileName());

    getline(file, line);
    std::stringstream stream(line);
    string token;
    // Tokenizing w.r.t. space ' '
    while (getline(stream, token, ' ')) {
      tokens.push_back(token);
    }

    // Assign rows and columns
    rows = stoi(tokens[0]);
    columns = stoi(tokens[1]);
    Forest originalForest(rows, columns);
    Forest newForest(rows, columns);
    int currentRow = 0;
    int currentColumn = 0;

    // Verify that all cells are valid
    while (getline(file, line)) {
      for (char cell : line) {
        originalForest.updateCell(currentRow, currentColumn, cell);
        currentColumn++;
      }

      currentRow++;
      currentColumn = 0;
    }

    this->staffOfAvalon.updateForest(workOrder->getFileName(), &originalForest,
                                     &newForest, workOrder->getPrintAllNights(),
                                     workOrder->getNights(), &outputFile);

    file.close();
    outputFile.close();
  }
}

size_t Wizard::getStart(size_t myRank, size_t workUnits, size_t workers) {
  size_t start =
      myRank * (workUnits / workers) + std::min(myRank, (workUnits % workers));

  if (start >= workUnits) {
    return workUnits;
  }

  return start;
}
size_t Wizard::getFinish(size_t processCount, size_t workUnits,
                         size_t workers) {
  return getStart(processCount + 1, workUnits, workers);
}
void Wizard::calculateMapsRange() {
  this->leftLimit =
      this->getStart(this->myRank, this->workOrders.size(), this->processCount);
  this->rightLimit = this->getFinish(this->myRank, this->workOrders.size(),
                                     this->processCount);
}

Wizard::Wizard(int my_rank, int process_count)
    : myRank(my_rank), processCount(process_count) {}
