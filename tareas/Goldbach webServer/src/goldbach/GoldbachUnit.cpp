#include "GoldbachUnit.hpp"

#include <cstdlib>
GoldbachUnit::GoldbachUnit(bool isPair, bool displaySums, int64_t number,
                           bool isValid, size_t sumsCount) {
  this->isPair = isPair;
  this->displaySums = displaySums;
  this->number = number;
  this->isValid = isValid;
  this->sumsCount = sumsCount;
}


GoldbachUnit::~GoldbachUnit() = default;

void GoldbachUnit::appendToSums(int64_t value) { this->sums.push_back(value); }

// Setters and getters
// Setters and getters
bool GoldbachUnit::getIsPair() { return this->isPair; }

void GoldbachUnit::setIsPair(bool isPair) { this->isPair = isPair; }

bool GoldbachUnit::getDisplaySums() { return this->displaySums; }

void GoldbachUnit::setDisplaySums(bool displaySums) {
  this->displaySums = displaySums;
}

std::vector<int64_t> &GoldbachUnit::getSums() { return this->sums; }

void GoldbachUnit::setSums(std::vector<int64_t> sums) { this->sums = sums; }

int64_t GoldbachUnit::getNumber() { return this->number; }

void GoldbachUnit::setNumber(int64_t number) { this->number = number; }

bool GoldbachUnit::isIsValid() { return this->isValid; }

void GoldbachUnit::setIsValid(bool isValid) { this->isValid = isValid; }

size_t GoldbachUnit::getSumsCount() { return this->sumsCount; }

void GoldbachUnit::setSumsCount(size_t sumsCount) {
  this->sumsCount = sumsCount;
}
