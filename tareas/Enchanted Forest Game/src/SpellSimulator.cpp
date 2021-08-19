// Copyright 2021 Josef Ruzicka, Samantha Romero, Carlos Solorzano. Universidad
// de Costa Rica.

#include "SpellSimulator.h"

#include <omp.h>

#include <string>
#include <utility>
#include <vector>

#include "Forest.h"

void SpellSimulator::updateForest(std::string originalForestName,
                                  Forest* originalForest, Forest* newForest,
                                  bool saveAllMaps, int nights,
                                  std::ofstream* archivoSalida) {
  std::string forests;
  std::cout
      << "--------------------------------------------------------------------"
         "---\n\n";
  std::cout << originalForestName << std::endl;
  std::cout << "nights" << nights << std::endl;

  int night;

  forests += "0:\n";
  originalForest->forestToString(forests);
  int rows = originalForest->getRows();
  int columns = originalForest->getColumns();
  int row;

  Forest* temporalptr = nullptr;
  Forest* originalForestptr = originalForest;
  Forest* currentForestptr = newForest;
  for (night = 0; night < nights; night++) {
#pragma omp parallel for default(none) schedule(static) \
    shared(columns, rows, originalForestptr, currentForestptr) collapse(2)
    for (row = 0; row < rows; row++) {
      for (int column = 0; column < columns; column++) {
        this->transformCell(originalForestptr, currentForestptr, row, column);
      }
    }

    // append currentForest to forests string.
    if (saveAllMaps || night == nights - 1) {
      forests += std::to_string(night + 1) + ":\n";

      currentForestptr->forestToString(forests);
    }

    // Switch pointers
    temporalptr = originalForestptr;
    originalForestptr = currentForestptr;
    currentForestptr = temporalptr;
  }
  this->saveForestOnTxt(night, archivoSalida, originalForestName, forests);
}

void SpellSimulator::transformCell(Forest* originalForest, Forest* newForest,
                                   int row, int column) {
  char currentCell = (originalForest->getMatrix())[row][column];

  if (currentCell == 'a') {
    // check flood
    if (this->checkTransformation(originalForest, row, column, currentCell,
                                  'l')) {
      newForest->updateCell(row, column, 'l');
      // check overcrowding
    } else if (this->checkTransformation(originalForest, row, column,
                                         currentCell, 'a')) {
      newForest->updateCell(row, column, '-');
    } else {
      // stay the same
      newForest->updateCell(row, column, 'a');
    }
  } else if (currentCell == 'l') {
    // check drought
    if (this->checkTransformation(originalForest, row, column, currentCell,
                                  'l')) {
      newForest->updateCell(row, column, '-');
    } else {
      newForest->updateCell(row, column, 'l');
    }
  } else if (currentCell == '-') {
    // check reforestation
    if (this->checkTransformation(originalForest, row, column, currentCell,
                                  'a')) {
      newForest->updateCell(row, column, 'a');
    } else {
      newForest->updateCell(row, column, '-');
    }
  }
}

int SpellSimulator::saveForestOnTxt(int night, std::ofstream* mapFile,
                                    std::string originalMapName,
                                    std::string forests) {
  std::string newName = this->obtainNewName(night, originalMapName);
  std::cout << newName << std::endl;
  mapFile->open(newName, std::ios::out);
  *mapFile << forests;
  mapFile->close();
  return EXIT_SUCCESS;
}

std::string SpellSimulator::obtainNewName(int currentNight,
                                          std::string fileName) {
  std::string newName;
  std::cout << "nombre que entra " << fileName << std::endl;
  newName += '-';
  newName += std::to_string(currentNight);
  newName += ".txt";
  fileName.replace(fileName.find('.'), fileName.length(), newName);

  return fileName;
}

bool SpellSimulator::checkTransformation(Forest* originalForest, int row,
                                         int column, char myValue,
                                         char ruleValue) {
  int valueCount = 0;

  std::vector<std::vector<char>>* matrix = &originalForest->getMatrix();

  bool left = true;
  bool right = true;
  bool topLeft = true;
  bool topRight = true;
  bool bottomRight = true;
  bool bottomLeft = true;
  bool bottom = true;
  bool top = true;
  originalForest->checkNeighbours(row, column, &top, &bottom, &left, &right,
                                  &bottomLeft, &bottomRight, &topLeft,
                                  &topRight);

  if (left && (*matrix)[row][column - 1] == ruleValue) {
    valueCount++;
  }

  if (topLeft && (*matrix)[row - 1][column - 1] == ruleValue) {
    valueCount++;
  }

  if (top && (*matrix)[row - 1][column] == ruleValue) {
    valueCount++;
  }

  if (topRight && (*matrix)[row - 1][column + 1] == ruleValue) {
    valueCount++;
  }

  if (right && (*matrix)[row][column + 1] == ruleValue) {
    valueCount++;
  }

  if (bottomRight && (*matrix)[row + 1][column + 1] == ruleValue) {
    valueCount++;
  }
  if (bottomLeft && (*matrix)[row + 1][column - 1] == ruleValue) {
    valueCount++;
  }

  if (bottom && (*matrix)[row + 1][column] == ruleValue) {
    valueCount++;
  }

  // flood or overCrowding.
  if (myValue == 'a' && ((valueCount >= 4 && ruleValue == 'l') ||
                         (valueCount > 4 && ruleValue == 'a'))) {
    return true;
  }
  // reforestation.
  if (myValue == '-' && valueCount >= 3) {
    return true;
  }
  // drought
  if (myValue == 'l' && valueCount < 3) {
    return true;
  }
  return false;
}
