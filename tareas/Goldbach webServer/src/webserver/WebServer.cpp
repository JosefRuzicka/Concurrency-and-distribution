// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0

#include "WebServer.hpp"

#include <GoldbachWebApp.hpp>
#include <Queue.hpp>
#include <cassert>
#include <iostream>
#include <regex>
#include <stdexcept>
#include <string>

#include "NetworkAddress.hpp"
WebServer* WebServer::instance = 0;

const char* const usage =
    "Usage: webserv [port] [max_connections]\n"
    "\n"
    "  port             Network port to listen incoming HTTP requests, "
    "default " DEFAULT_PORT
    "\n"
    "  max_connections  Maximum number of allowed client connections\n";

WebServer::WebServer() {}

WebServer* WebServer::getInstance() {
  if (instance == 0) {
    instance = new WebServer();
  }
  return instance;
}

void WebServer::createRequestHandler() {
  this->createHttpConnectionHandlers(this->maxConnections);
  this->requestHandler->setConsumingQueue(&this->requests);
  this->requestHandler->registerRedirect(
      "mathRequest", &this->goldbachWebApp->getMathRequests());
  this->requestHandler->registerRedirect(
      "standardRequest", &this->goldbachWebApp->getStandardRequests());
  this->requestHandler->startThread();
}

int WebServer::start(int argc, char* argv[]) {
  try {
    if (this->analyzeArguments(argc, argv)) {
      // create threads (HttpConnectionHandlers)
      this->goldbachWebApp = new GoldbachWebApp();
      this->createRequestHandler();
      this->listenForConnections(this->port);
      const NetworkAddress& address = this->getNetworkAddress();
      std::cout << "web server listening on " << address.getIP() << " port "
                << address.getPort() << "...\n";
      this->acceptAllConnections();
    }
  } catch (const std::runtime_error& error) {
    std::cerr << "error: " << error.what() << std::endl;
  }

  return EXIT_SUCCESS;
}

bool WebServer::analyzeArguments(int argc, char* argv[]) {
  // Traverse all arguments
  for (int index = 1; index < argc; ++index) {
    const std::string argument = argv[index];
    if (argument.find("help") != std::string::npos) {
      std::cout << usage;
      return false;
    }
  }

  if (argc >= 2) {
    this->port = argv[1];
  }

  if (argc >= 3) {
    if (sscanf(argv[2], "%zu", &this->maxConnections) != 1 || errno) {
      fprintf(stderr, "error: invalid thread count\n");
    }
  }

  return true;
}

size_t WebServer::getMaxConnections() { return maxConnections; }

// //}

// void WebServer::stopCalculators() {
//   for (size_t calculator = 0; calculator < this->calculators.size();
//        calculator++) {
//     this->orders.push(GoldbachOrder());
//   }
//   this->joinCalculators();
// }

// void WebServer::joinCalculators() {
//   for (size_t calculator = 0; calculator < this->calculators.size();
//        calculator++) {
//     this->calculators[calculator]->waitToFinish();
//   }
// }
