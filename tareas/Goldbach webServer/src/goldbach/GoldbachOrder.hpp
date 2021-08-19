//
// Created by charlie on 7/10/21.
//

#ifndef AVANCE_02_SRC_GOLDBACH_GOLDBACHORDER_HPP_
#define AVANCE_02_SRC_GOLDBACH_GOLDBACHORDER_HPP_

#include <cstdint>
#include <vector>

#include "HttpRequest.hpp"
#include "HttpResponse.hpp"

class GoldbachOrder {
 private:
  /// client request
  Socket socket;
  /// vector of requested numbers
  std::vector<int64_t> entries;
  /// highest requested number
  int64_t highest_number;
  /// finder of stopCondition
  bool isStopCondition = true;

 public:
  /// constructor with params
  GoldbachOrder(const Socket &socket);
  /// constructor
  GoldbachOrder();
  /// destructor
  virtual ~GoldbachOrder();

  /**
   *  @brief: returns highest number.
   */
  const int64_t &GetHighestNumber() const;

  /**
   *  @brief: setter for highestNumber.
   */
  void SetHighestNumber(const int64_t &highest_number);

  /**
   *  @brief: setter for isStopCondition.
   */
  void setIsStopCondition(bool isStopCondition);

  /**
   *  @brief: setter for entries.
   */
  void setEntries(std::vector<int64_t> entries);

  /// operator override.
  bool operator==(const GoldbachOrder &other) const;

  /**
   *  @brief: returns entries vector.
   */
  const std::vector<int64_t> &GetEntries() const;

  /**
   *  @brief: setter for entries via reference.
   */
  void SetEntries(const std::vector<int64_t> &entries);

  /**
   *  @brief: returns the socket that holds a client request.
   */
  const Socket &GetSocket() const;
};

#endif  // AVANCE_02_SRC_GOLDBACH_GOLDBACHORDER_HPP_
