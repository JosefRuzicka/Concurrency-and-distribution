#include "GoldbachProccessedMathOrder.hpp"

GoldbachProccessedMathOrder::GoldbachProccessedMathOrder(
    const Socket &socket, std::vector<GoldbachUnit> &goldbachUnits)
    : socket(socket) {
  this->processedGolbachUnits.swap(goldbachUnits);
}
GoldbachProccessedMathOrder::GoldbachProccessedMathOrder() {}

GoldbachProccessedMathOrder::~GoldbachProccessedMathOrder() {}

const Socket &GoldbachProccessedMathOrder::getSocket() const {
  return this->socket;
}

const std::vector<GoldbachUnit> &GoldbachProccessedMathOrder::getGoldbachUnits()
    const {
  return this->processedGolbachUnits;
}

bool GoldbachProccessedMathOrder::operator==(
    const GoldbachProccessedMathOrder &other) const {
  return this->socket == other.socket;
}
