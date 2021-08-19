// Copyright 2021 Josef Ruzicka, Samantha Romero, Carlos Solorzano. Universidad
// de Costa Rica.
/**
 * Forest class. holds and handles a char matrix.
 * Programmed by Josef Ruzicka, Samantha Romero and Carlos Solorzano.
 */

#ifndef _FOREST_H
#define _FOREST_H
#include <fstream>
#include <iostream>
#include <vector>
class Forest {
 public:
  /**
   * @brief: constructor.
   */
  Forest(int rows, int columns);

  /**
   * @brief: destructor.
   */
  ~Forest();

  /**
   * @returns Number of columns.
   */
  int getColumns();

  /**
   * @returns Number of rows.
   */
  int getRows();

  /**
   * @brief: verifies which neighbours exist for a cell.
   * @param row
   * @param column
   * @param upper
   * @param down
   * @param left
   * @param right
   * @param downLeft
   * @param downRight
   * @param upperLeft
   * @param upperRight
   */
  void checkNeighbours(int row, int column, bool *upper, bool *down, bool *left,
                       bool *right, bool *downLeft, bool *downRight,
                       bool *upperLeft, bool *upperRight);

  /**
   * @brief: updates a cell to a certain value.
   * @param row
   * @param column
   * @param value
   */
  void updateCell(int row, int column, char value);

  /**
   *  @brief draws the map of the forest into an std::string
   */
  void forestToString(std::string &forests);

 private:
  int rows;
  int columns;

 public:
  /**
   * @brief: matrix getter.
   */
  std::vector<std::vector<char>> &getMatrix();

  // matrix.
  std::vector<std::vector<char>> matrix;

 private:
  /**
   * @brief: checks if cell belongs to the perimeter of the matrix.
   * @param row
   * @param column
   */
  bool isFromPerimeter(int row, int column);

  /**
   * @brief: checks if cell belongs to the left side of the perimeter of the
   * matrix.
   * @param row
   * @param column
   */
  bool isFromLeftSide(int column);

  /**
   * @brief: checks if cell belongs to the right side of the perimeter of the
   * matrix.
   * @param row
   * @param column
   */
  bool isFromRightSide(int column);

  /**
   * @brief: checks if cell belongs to the top side of the perimeter of the
   * matrix.
   * @param row
   * @param column
   */
  bool isFromUpperSide(int row);

  /**
   * @brief: checks if cell belongs to the bottom side of the perimeter of the
   * matrix.
   * @param row
   * @param column
   */
  bool isFromDownSide(int row);

  /**
   * @brief: checks if cell belongs to the top-left side of the perimeter of the
   * matrix.
   * @param row
   * @param column
   */
  bool isFromUpperLeft(int row, int column);

  /**
   * @brief: checks if cell belongs to the top-right side of the perimeter of
   * the matrix.
   * @param row
   * @param column
   */
  bool isFromUpperRight(int row, int column);

  /**
   * @brief: checks if cell belongs to the bottom-left side of the perimeter of
   * the matrix.
   * @param row
   * @param column
   */
  bool isFromDownLeft(int row, int column);

  /**
   * @brief: checks if cell belongs to the bottom-right side of the perimeter of
   * the matrix.
   * @param row
   * @param column
   */
  bool isFromDownRight(int row, int column);

  /**
   * @brief row value setter.
   */
  void setRows(int rows);

  /**
   * @brief columns value setter.
   */
  void setColumns(int columns);
};

#endif  //_FOREST_H
