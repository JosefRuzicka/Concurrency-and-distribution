#ifndef GOLDBACHPROCCESSEDMATHORDER_H
#define GOLDBACHPROCCESSEDMATHORDER_H
#pragma once

#include <vector>

#include "GoldbachUnit.hpp"
#include "Socket.hpp"

class GoldbachProccessedMathOrder {
 private:
  Socket socket;
  std::vector<GoldbachUnit> processedGolbachUnits;

 public:
  GoldbachProccessedMathOrder(const Socket &socket,
                              std::vector<GoldbachUnit> &goldbachUnits);

  GoldbachProccessedMathOrder();

  ~GoldbachProccessedMathOrder();

  const Socket &getSocket() const;
  const std::vector<GoldbachUnit> &getGoldbachUnits() const;

  /// operator override.
  bool operator==(const GoldbachProccessedMathOrder &other) const;
};
#endif