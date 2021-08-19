/**
 * Work order class. holds a map and its attributes in order for a process to
 * work on it. Programmed by Josef Ruzicka, Samantha Romero and Carlos
 * Solorzano.
 */

#ifndef _WORKORDER_H
#define _WORKORDER_H

#include <iostream>

class WorkOrder {
 public:
  /**
   * @brief: constructor.
   * @param nights: number of nights for the simulation to be run.
   * @param fileName: map file name.
   * @param printNights: whether or not the forest should be printed every
   * midnight.
   */
  WorkOrder(int nights, std::string fileName, bool printNights);

  /**
   * @brief: destructor.
   */
  ~WorkOrder();

  /**
   * @brief: file name getter.
   */
  const std::string getFileName();

  /**
   * @brief: nights value getter.
   */
  int getNights();

  /**
   * @brief: isValid value setter.
   */
  void setIsValid(bool workOrderisValid);

  /**
   * @brief: printAllNights value getter.
   */
  bool getPrintAllNights();

 private:
  std::string fileName;
  int nights;
  bool printAllNights;
  bool isValid;
};

#endif  //_WORKORDER_H
