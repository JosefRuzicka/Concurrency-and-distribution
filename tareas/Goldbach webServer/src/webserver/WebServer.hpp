// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0

#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <GoldbachCalculator.hpp>
#include <GoldbachOrder.hpp>
#include <GoldbachWebApp.hpp>

#include "HttpServer.hpp"

#define DEFAULT_PORT "8080"

class WebServer : public HttpServer {
  DISABLE_COPY(WebServer);

 private:
  /// TCP port where this web server will listen for connections
  const char* port = DEFAULT_PORT;
  /// default number of httpConnectionHandlers made available
  size_t maxConnections = 1000;
  // // /// default number of goldbach calculators will be the systems active
  // // /// processors.
  //  size_t maxCalculators;

  GoldbachWebApp* goldbachWebApp;
  /// goldbach calculators consumingQueue, contains the requested numbers of
  /// each client.
  // Queue<GoldbachOrder> orders;
  // // vector of goldbach calculators.
  // std::vector<GoldbachCalculator*> calculators;
  /// singleton identity of the server.
  static WebServer* instance;
  /// Constructor
  WebServer();
  /// Destructor
  ~WebServer() = default;
  void createRequestHandler();

 public:
  /**
   * @brief: Returns max_connections
   */
  size_t getMaxConnections();

 public:
  /// Singleton instance Getter
  static WebServer* getInstance();
  /// Start the simulation
  int start(int argc, char* argv[]);

  // /**
  //  * @brief: Fills the calculator threads consuming queue with empty
  //  * goldbachOrders which are recognized as stopConditions.
  //  */
  // void stopCalculators();

  // /**
  //  * @brief: Waits for every calculator thread to finish its task.
  //  */
  // void joinCalculators();

 protected:
  /// Analyze the command line arguments
  /// @return true if program can continue execution, false otherwise
  bool analyzeArguments(int argc, char* argv[]);

  // /**
  //  * @brief: creates and starts calculator threads
  //  */
  // void createCalculators();
};

#endif  // WEBSERVER_H
