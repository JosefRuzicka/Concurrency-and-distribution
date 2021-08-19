// Copyright 2021 Josef Ruzicka, Samantha Romero, Carlos Solorzano. Universidad
// de Costa Rica.
#include <string>
#include "WorkOrder.h"

// Access to private members of WorkOrder
WorkOrder::WorkOrder(int nights, std::string fileName, bool printNights) {
  this->nights = nights;
  this->fileName = fileName;
  this->printAllNights = printNights;
  this->isValid = true;
}

WorkOrder::~WorkOrder() {}

const std::string WorkOrder::getFileName() { return this->fileName; }

bool WorkOrder::getPrintAllNights() { return this->printAllNights; }

void WorkOrder::setIsValid(bool workOrderisValid) {
  this->isValid = workOrderisValid;
}
int WorkOrder::getNights() { return this->nights; }
