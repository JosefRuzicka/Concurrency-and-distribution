#include "GoldbachCalculator.hpp"

#include <cmath>
#include <cstdio>
#include <iostream>

#include "GoldbachProccessedMathOrder.hpp"
#include "GoldbachWebApp.hpp"

GoldbachCalculator::~GoldbachCalculator() = default;

void GoldbachCalculator::calculateSums(int64_t highestNumber) {
  this->getPrimes(highestNumber);

  for (auto& goldbachUnit : this->goldbachUnits) {
    if (goldbachUnit.getIsValid()) {
      if (goldbachUnit.getIsEven()) {
        calculateEvenSums(&goldbachUnit);
      } else {
        calculateOddSums(&goldbachUnit);
      }
    }
  }
}

void GoldbachCalculator::calculateEvenSums(GoldbachUnit* gEvenUnit) {
  int64_t sum = 0;
  size_t primesQuantity = 0;
  size_t sumsCount = 0;
  bool isLower = true;

  while (isLower && primesQuantity < this->primesArray.size()) {
    if (this->primesArray[primesQuantity] >= gEvenUnit->getNumber()) {
      isLower = false;
    }
    primesQuantity++;
  }

  // Calculates all possible sums
  if (primesQuantity != -0) {
    for (size_t posPrime = 0; posPrime < primesQuantity; posPrime++) {
      for (size_t posPrime2 = posPrime; posPrime2 < primesQuantity;
           posPrime2++) {
        int64_t prime1 = this->primesArray[posPrime];
        int64_t prime2 = this->primesArray[posPrime2];
        sum = prime1 + prime2;
        // If the result of variable <sum> is the goldbach unit number stores
        // the number on the goldbach unit sums array
        if (sum == gEvenUnit->getNumber()) {
          gEvenUnit->getSums().push_back(prime1);
          gEvenUnit->getSums().push_back(prime2);
          sumsCount++;
        }
      }
    }
  } else {
    printf("ERROR: getPrimes()\n");
  }
  // Assign sums count to the g_unit
  gEvenUnit->setSumsCount(sumsCount);
}

void GoldbachCalculator::calculateOddSums(GoldbachUnit* gUnitOdd) {
  int64_t sum = 0;
  int64_t sumsCount = 0;
  size_t primesQuantity = 0;
  bool isLower = true;

  // Calculates how many primes are lower than the goldbach unit value
  while (isLower && primesQuantity < this->primesArray.size()) {
    if (this->primesArray[primesQuantity] >= gUnitOdd->getNumber()) {
      isLower = false;
    }
    primesQuantity++;
  }

  // Calculates all possible sums
  for (size_t posPrime = 0; posPrime < primesQuantity; posPrime++) {
    for (size_t posPrimo2 = posPrime; posPrimo2 < primesQuantity; posPrimo2++) {
      for (size_t posPrime3 = posPrimo2; posPrime3 < primesQuantity;
           posPrime3++) {
        int64_t prime1 = this->primesArray[posPrime];
        int64_t prime2 = this->primesArray[posPrimo2];
        int64_t prime3 = this->primesArray[posPrime3];

        sum = prime1 + prime2 + prime3;
        // If the result of variable <sum> is the goldbach unit number stores
        // the number on the goldbach unit sums array
        if (sum == gUnitOdd->getNumber()) {
          gUnitOdd->getSums().push_back(prime1);
          gUnitOdd->getSums().push_back(prime2);
          gUnitOdd->getSums().push_back(prime3);

          sumsCount++;
        }
      }
    }
  }
  // Assign sums count to the g_unit

  gUnitOdd->setSumsCount(sumsCount);
}

int64_t GoldbachCalculator::getPrimes(int64_t number) {
  bool isPrime = true;
  this->primesArray.push_back(2);
  this->primesArray.push_back(3);
  this->primesArray.push_back(5);

  for (int64_t possiblePrime = 6; possiblePrime < number; possiblePrime++) {
    isPrime = true;
    for (int64_t divider = 2; divider <= sqrtl(possiblePrime) && isPrime;
         divider++) {
      if ((possiblePrime % divider) == 0) {
        isPrime = false;
      }
    }
    if (isPrime) {
      this->primesArray.push_back(possiblePrime);
    }
  }
  return 0;
}
int GoldbachCalculator::run() {
  this->consumeForever();
  return 0;
}

void GoldbachCalculator::consume(const GoldbachOrder& data) {
  this->createGoldbachUnits(data.GetEntries());
  this->calculateSums(data.GetHighestNumber());

  GoldbachProccessedMathOrder proccessedOrder(data.GetSocket(),
                                              this->goldbachUnits);

  this->produce(proccessedOrder);

  this->goldbachUnits.clear();
  this->primesArray.clear();
}
void GoldbachCalculator::SetIndex(int index) {
  GoldbachCalculator::index = index;
}
GoldbachCalculator::GoldbachCalculator() = default;

int GoldbachCalculator::createGoldbachUnits(
    const std::vector<int64_t>& entries) {
  for (auto& entry : entries) {
    this->processEntry(entry);
  }

  return EXIT_SUCCESS;
}

void GoldbachCalculator::processEntry(int64_t entry) {
  GoldbachUnit g_unit;

  bool isValid = true;

  if (entry < 0) {
    g_unit.setDisplaySums(true);
  } else {
    g_unit.setDisplaySums(false);
  }
  int64_t pureValue = 0;
  pureValue = llabs(entry);

  if (pureValue <= 5) {
    isValid = false;
  }

  if (this->isEven(pureValue)) {
    g_unit.setIsEven(true);
  } else {
    g_unit.setIsEven(false);
  }
  g_unit.setNumber(pureValue);
  g_unit.setIsValid(isValid);

  this->goldbachUnits.push_back(g_unit);
}

bool GoldbachCalculator::isEven(int64_t number) {
  if (number % 2 == 0) {
    return true;
  }
  return false;
}
