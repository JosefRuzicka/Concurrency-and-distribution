// Created by Carlos Solorzano

#ifndef GOLDBACHUNIT_H
#define GOLDBACHUNIT_H

#include <cstdint>
#include <vector>

class GoldbachUnit {
 private:
  /**
   * @brief Stores data of a goldbach unit
   *
   * @var isPair Indicate if number stored is pair
   * @var displaySums Indicate if user wants to display goldbach sums
   * @var sums Array of sums
   * @var sumsCount Quantity of sums
   * @var number Number stored
   * @var isValid Indicate if number is valid
   * */
  bool isPair;
  bool displaySums;
  std::vector<int64_t> sums;
  int64_t number;
  bool isValid;
  size_t sumsCount;

 public:
  /// constructor
  explicit GoldbachUnit(bool isPair = false, bool displaySums = false,
                        int64_t number = 0, bool isValid = false,
                        size_t sumsCount = 0);

  // Error if asked to create own queue
  /// destructor
  ~GoldbachUnit();

  /**
   *  @brief: Method to add sums
   */
  void appendToSums(int64_t value);

  // Setters and getters

  /**
   *  @brief: returns true if number is even.
   */
  bool getIsPair();
  /**
   *  @brief: setter for isPair.
   */
  void setIsPair(bool isPair);

  /**
   *  @brief: returns true if number is negative.
   */
  bool getDisplaySums();

  /**
   *  @brief: setter for displaySums.
   */
  void setDisplaySums(bool displaySums);

  /**
   *  @brief: returns vector of sums.
   */
  std::vector<int64_t> &getSums();

  /**
   *  @brief: setter for vector of Sums.
   */
  void setSums(std::vector<int64_t> sums);

  /**
   *  @brief: returns number value.
   */
  int64_t getNumber();

  /**
   *  @brief: setter for number value.
   */
  void setNumber(int64_t number);

  /**
   *  @brief: returns true if number is valid.
   */
  bool isIsValid();

  /**
   *  @brief: setter for isValid.
   */
  void setIsValid(bool isValid);

  /**
   *  @brief: returns sums count.
   */
  size_t getSumsCount();

  /**
   *  @brief: setter for sumsCount.
   */
  void setSumsCount(size_t sumsCount);
};

#endif
