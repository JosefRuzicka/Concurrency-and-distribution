//
// Created by charlie on 7/10/21.
//

#include "GoldbachOrder.hpp"

#include <cstdint>
#include <iostream>

GoldbachOrder::~GoldbachOrder() {}

const int64_t &GoldbachOrder::GetHighestNumber() const {
  return highest_number;
}
void GoldbachOrder::SetHighestNumber(const int64_t &highest_number) {
  GoldbachOrder::highest_number = highest_number;
}

bool GoldbachOrder::operator==(const GoldbachOrder &other) const {
  return this->isStopCondition == other.isStopCondition;
}

void GoldbachOrder::setIsStopCondition(bool isStopCondition) {
  this->isStopCondition = isStopCondition;
}

const std::vector<int64_t> &GoldbachOrder::GetEntries() const {
  return entries;
}
void GoldbachOrder::SetEntries(const std::vector<int64_t> &entries) {
  GoldbachOrder::entries = entries;
}

GoldbachOrder::GoldbachOrder(const Socket &socket) : socket(socket) {}

const Socket &GoldbachOrder::GetSocket() const { return socket; }

void GoldbachOrder::setEntries(std::vector<int64_t> entries) {
  for (long &entrie : entries) {
    this->entries.push_back(entrie);
  }
}
GoldbachOrder::GoldbachOrder() {}
