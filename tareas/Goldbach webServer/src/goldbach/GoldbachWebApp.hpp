// Created by Carlos Solorzano

#ifndef GOLDBACHWEBAPP_HPP_
#define GOLDBACHWEBAPP_HPP_
#include <string>

#include "../http/HttpRequest.hpp"
#include "../http/HttpResponse.hpp"
#include "GoldbachCalculator.hpp"
#include "GoldbachMathOrderBuilder.hpp"
#include "GoldbachMathOrderResponseHandler.hpp"
#include "GoldbachStandardResponseHandler.hpp"
#include "GoldbachUnit.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "Queue.hpp"
/**
 * GoldbachWebApp which is responsible for receiving the http requests made by
 * the client, extracting the numbers, passing them to the goldbachCalculator,
 * obtaining the sums, assembling and dispatching the HTTP responses
 *
 */
class GoldbachWebApp {
 private:
  // goldbach calculators consumingQueue, contains the requested numbers of
  /// each client.

  Queue<HttpRequest> mathRequests;
  Queue<HttpRequest> standardRequests;
  Queue<GoldbachOrder> unprocessedMathOrders;
  Queue<GoldbachProccessedMathOrder> processedMathOrders;

  // vector of goldbach calculators.
  std::vector<GoldbachCalculator *> calculators;
  /// default number of goldbach calculators will be the systems active
  /// processors.
  size_t maxCalculators;

  GoldbachMathOrderBuilder *mathOrderbuilder;
  GoldbachMathOrderResponseHandler *mathOrderResponseHandler;
  GoldbachStandardResponseHandler *standardResponseHandler;

 public:
  /// Constructor
  explicit GoldbachWebApp();
  /// destructor
  virtual ~GoldbachWebApp();

  /**
   * @brief: Assembles the goldBachUnit results into a string usable in the
   * httpResponseBody.
   */
  static std::string assemblyHttpResponseBody(
      const std::vector<GoldbachUnit> &goldbachUnits);

  /**
   * @brief: Fills the calculator threads consuming queue with empty
   * goldbachOrders which are recognized as stopConditions.
   */
  void stopCalculators();

  /**
   * @brief: Waits for every calculator thread to finish its task.
   */
  void joinCalculators();

  /**
   * @brief: creates and starts calculator threads
   */
  void createCalculators();

  Queue<HttpRequest> &getMathRequests();
  Queue<HttpRequest> &getStandardRequests();
};
#endif  // GOLDBACHWEBAPP_HPP_
