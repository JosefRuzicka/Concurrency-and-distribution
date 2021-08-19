// Copyright 2021 Josef Ruzicka, Samantha Romero, Carlos Solorzano. Universidad
// de Costa Rica.

#include "Forest.h"

#include <omp.h>

#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>

#include "SpellSimulator.h"

Forest::Forest(int rows, int columns) {
  this->rows = rows;
  this->columns = columns;

  this->matrix.resize(this->rows);

  for (int row = 0; row < this->rows; row++) {
    this->matrix[row].resize(this->columns);
  }
}

Forest::~Forest() { this->matrix.clear(); }

int Forest::getColumns() { return this->columns; }

int Forest::getRows() { return this->rows; }

void Forest::forestToString(std::string &forests) {
  for (int row = 0; row < this->rows; row++) {
    for (int column = 0; column < this->columns; column++) {
      forests += this->matrix[row][column];
    }
    forests += "\n";
  }
}

void Forest::checkNeighbours(int row, int column, bool *upper, bool *down,
                             bool *left, bool *right, bool *downLeft,
                             bool *downRight, bool *upperLeft,
                             bool *upperRight) {
  // Check if current Cell belongs to perimeter.
  if (isFromPerimeter(row, column)) {
    // Check if current Cell belongs to the left side.
    if (isFromLeftSide(column)) {
      *left = false;
      *upperLeft = false;
      *downLeft = false;
      // Check if current Cell belongs to the upper left side.
      if (isFromUpperLeft(row, column)) {
        *upper = false;
        *upperRight = false;

      } else if (isFromDownLeft(row, column)) {
        // Check if current Cell belongs to the bottom left side.
        *down = false;
        *downRight = false;
      }
    } else if (isFromRightSide(column)) {
      // Check if current Cell belongs to the right side.
      *right = false;
      *upperRight = false;
      *downRight = false;
      if (isFromUpperRight(row, column)) {
        // Check if current Cell belongs to the upper right side.
        *upper = false;
        *upperLeft = false;
      } else if (isFromDownRight(row, column)) {
        // Check if current Cell belongs to the bottom right side.
        *down = false;
        *downLeft = false;
      }
    } else if (isFromUpperSide(row)) {
      // Check if current Cell belongs to the upper side.
      *upper = false;
      *upperLeft = false;
      *upperRight = false;
    } else if (isFromDownSide(row)) {
      // Check if current Cell belongs to the bottom side.
      *down = false;
      *downLeft = false;
      *downRight = false;
    }
  }
}

void Forest::updateCell(int row, int column, char value) {
  this->matrix[row][column] = value;
}

bool Forest::isFromPerimeter(int row, int column) {
  if (column == 0 || column == this->columns - 1 || row == 0 ||
      row == this->rows - 1) {
    return true;
  }
  return false;
}

bool Forest::isFromLeftSide(int column) {
  if (column == 0) {
    return true;
  }
  return false;
}

bool Forest::isFromRightSide(int column) {
  if (column == this->columns - 1) {
    return true;
  }
  return false;
}

bool Forest::isFromUpperSide(int row) {
  if (row == 0) {
    return true;
  }
  return false;
}

bool Forest::isFromDownSide(int row) {
  if (row == this->rows - 1) {
    return true;
  }
  return false;
}

bool Forest::isFromUpperLeft(int row, int column) {
  if (row == 0 && column == 0) {
    return true;
  }
  return false;
}

bool Forest::isFromUpperRight(int row, int column) {
  if (row == 0 && column == this->columns - 1) {
    return true;
  }
  return false;
}

bool Forest::isFromDownLeft(int row, int column) {
  if (row == this->rows - 1 && column == 0) {
    return true;
  }
  return false;
}

bool Forest::isFromDownRight(int row, int column) {
  if (row == this->rows - 1 && column == this->columns - 1) {
    return true;
  }
  return false;
}

void Forest::setRows(int rows) { this->rows = rows; }

void Forest::setColumns(int columns) { this->columns = columns; }

std::vector<std::vector<char>> &Forest::getMatrix() { return this->matrix; }
