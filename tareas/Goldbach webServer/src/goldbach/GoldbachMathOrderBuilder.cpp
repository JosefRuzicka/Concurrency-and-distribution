#include "GoldbachMathOrderBuilder.hpp"

#include <regex>

GoldbachMathOrderBuilder::GoldbachMathOrderBuilder() {}

GoldbachMathOrderBuilder::~GoldbachMathOrderBuilder() {}

int GoldbachMathOrderBuilder::run() {
  this->consumeForever();
  return EXIT_SUCCESS;
}

void GoldbachMathOrderBuilder::consume(const HttpRequest& data) {
  std::smatch matches;

  // If a number was asked in the form "/goldbach/1223"
  // or "/goldbach?number=1223"
  std::regex inQuery(
      "^/goldbach(/|\\?number=)([\\-[0-9]+((?:,[-[0-9]+]*)?)*)$");

  std::regex_search(data.getURI(), matches, inQuery);

  // Tokenize
  const char delimiter = ',';
  std::string inputNumbersString = matches[2];
  std::vector<int64_t> inputNumbers;
  int64_t largestInputNumber = 0;
  int error = this->tokenize(inputNumbersString, delimiter, inputNumbers,
                             largestInputNumber);

  if (error == EXIT_SUCCESS) {
    GoldbachOrder order(data.getSocket());
    order.SetHighestNumber(largestInputNumber);
    order.SetEntries(inputNumbers);
    order.setIsStopCondition(false);
    this->produce(order);
  }
}

int GoldbachMathOrderBuilder::tokenize(std::string const& inputNumbersString,
                                       const char delimiter,
                                       std::vector<int64_t>& inputNumbers,
                                       int64_t& largestInputNumber) {
  std::stringstream stream(inputNumbersString);
  std::string numberString;
  int error = EXIT_SUCCESS;
  // Check all numbers.
  while (error == EXIT_SUCCESS &&
         std::getline(stream, numberString, delimiter)) {
    // Check if number is in range.
    if (llabs(std::stoll(numberString)) <= (9223372036854775807)) {
      // Check if number is the largestInputNumber.
      if (llabs(std::stoll(numberString)) > largestInputNumber) {
        largestInputNumber = llabs(std::stoll(numberString));
      }
      // Insert number in inputNumbers vector.
      inputNumbers.push_back(std::stoll(numberString));
    } else {
      error = EXIT_FAILURE;
    }
  }
  return error;
}
