// Created by Carlos Solorzano

#ifndef GOLDBACHMODEL_H
#define GOLDBACHMODEL_H
#include <cstdint>
#include <vector>

#include "Assembler.hpp"
#include "GoldbachOrder.hpp"
#include "GoldbachProccessedMathOrder.hpp"
#include "GoldbachUnit.hpp"

class GoldbachCalculator
    : public Assembler<GoldbachOrder, GoldbachProccessedMathOrder> {
  DISABLE_COPY(GoldbachCalculator);

 public:
  /// constructor
  GoldbachCalculator();

 private:
  /// vector of goldbach units
  std::vector<GoldbachUnit> goldbachUnits;
  /// vector of primeNumbers
  std::vector<int64_t> primesArray;
  /// position in a data structure.
  int index;

  void processEntry(int64_t entry);
  bool isEven(int64_t number);

  /**
   * @brief calculates all the prime int64_t integers from 2 to a given number
   * @param number int64_t numbers from zero to this number wil be processed
   * @return quantity of prime numbers found
   */
  int64_t getPrimes(int64_t number);

  /**
   * @brief Calculates all sums of 2 primes that add up to the value of
   * gUnitPair.
   * @param gUnitPair goldBach unit to be processed
   */
  void calculateEvenSums(GoldbachUnit *gEvenUnit);

  /**
   * @brief Calculates all sums of 3 primes that add up to the value of
   * gUnitOdd.
   * @param gUnitPair goldBach unit to be processed
   */
  void calculateOddSums(GoldbachUnit *gOddUnit);

  /**
   * @brief: for every inputNumber create a goldbach unit and append it to the
   * goldbach units vector.
   */
  int createGoldbachUnits(const std::vector<int64_t> &entries);

 public:
  /// starts this thread.
  int run() override;

  /**
   * @brief Setter for index.
   */
  void SetIndex(int index);

  /**
   *Override this method to process any data extracted from the queue
   */
  void consume(const GoldbachOrder &data) override;

  // GoldbachCalculator Destructor
  ~GoldbachCalculator();

  /**
   * @brief determines wether to call calculateSumsPair or calculateSumsOdd in
   * order to calculate all sums.
   */
  void calculateSums(int64_t highestNumber);
};

#endif