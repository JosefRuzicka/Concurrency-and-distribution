#include "GoldbachUnit.hpp"

#include <cstdlib>
GoldbachUnit::GoldbachUnit(bool isEven, bool displaySums, int64_t number,
                           bool isValid, size_t sumsCount) {
  this->isEven = isEven;
  this->displaySums = displaySums;
  this->number = number;
  this->isValid = isValid;
  this->sumsCount = sumsCount;
}

GoldbachUnit::~GoldbachUnit() = default;

void GoldbachUnit::appendToSums(int64_t value) { this->sums.push_back(value); }

// Setters and getters
bool GoldbachUnit::getIsEven() { return this->isEven; }

void GoldbachUnit::setIsEven(bool isEven) { this->isEven = isEven; }

bool GoldbachUnit::getDisplaySums() { return this->displaySums; }

void GoldbachUnit::setDisplaySums(bool displaySums) {
  this->displaySums = displaySums;
}

std::vector<int64_t> &GoldbachUnit::getSums() { return this->sums; }

void GoldbachUnit::setSums(std::vector<int64_t> sums) { this->sums = sums; }

int64_t GoldbachUnit::getNumber() { return this->number; }

void GoldbachUnit::setNumber(int64_t number) { this->number = number; }

bool GoldbachUnit::getIsValid() { return this->isValid; }

void GoldbachUnit::setIsValid(bool isValid) { this->isValid = isValid; }

size_t GoldbachUnit::getSumsCount() { return this->sumsCount; }

void GoldbachUnit::setSumsCount(size_t sumsCount) {
  this->sumsCount = sumsCount;
}
