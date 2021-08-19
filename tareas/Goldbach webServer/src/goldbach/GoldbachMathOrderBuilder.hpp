#ifndef GOLDBACHMATHORDERBUILDER_H
#define GOLDBACHMATHORDERBUILDER_H

#include "Assembler.hpp"
#include "GoldbachOrder.hpp"
#include "HttpRequest.hpp"
class GoldbachMathOrderBuilder : public Assembler<HttpRequest, GoldbachOrder> {
 private:
  /**
   * @brief Split a string of comma separated numbers into an int64_t vector.
   * Also keeps track of the largest number.
   * @param inputNumbersString: The string to be split.
   * @param delimiter: The delimiter that marks when to split. A comma in this
   * case.
   * @param inputNumbers: The array of int_64_t on which the input numbers will
   * be stored.
   * @param largestInputNumber: Will store the largest number.
   * @return true if comma separated numbers are valid and properly handled.
   */
  int tokenize(std::string const& inputNumbersString, const char delimiter,
               std::vector<int64_t>& inputNumbers, int64_t& largestInputNumber);

 public:
  GoldbachMathOrderBuilder();
  ~GoldbachMathOrderBuilder();

  /**
Override this method to start the thread's tasks.
*/
  int run() override;

  /**
Override this method to process any data extracted from the queue
*/
  void consume(const HttpRequest& data) override;
};
#endif