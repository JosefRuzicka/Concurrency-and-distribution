#include "HttpRequestHandler.hpp"

#include <iostream>
#include <regex>

#include "NetworkAddress.hpp"

HttpRequestHandler::HttpRequestHandler() {}

HttpRequestHandler::~HttpRequestHandler() {}

int HttpRequestHandler::run() {
  // Dispatch all the network messages we receive to their respective queues
  this->consumeForever();

  // If we exited from the forever loop, the finish message was received
  // For this simulation is OK to propagate it to all the queues
  for (const auto& pair : this->toQueues) {
    pair.second->push(HttpRequest());
  }

  return EXIT_SUCCESS;
}

std::string HttpRequestHandler::extractKey(const HttpRequest& data) const {
  // Print IP and port from client
  const NetworkAddress& address = data.getNetworkAddress();

  std::cout << "connection established with client " << address.getIP()
            << " port " << address.getPort() << std::endl;

  // Print HTTP request
  std::cout << "  " << data.getMethod() << ' ' << data.getURI() << ' '
            << data.getHttpVersion() << std::endl;
  std::smatch matches;
  std::regex inQuery(
      "^/goldbach(/|\\?number=)([\\-[0-9]+((?:,[-[0-9]+]*)?)*)$");

  if (std::regex_search(data.getURI(), matches, inQuery) &&
      matches.length() >= 3) {
    // If a number was asked in the form "/goldbach/1223"
    // or "/goldbach?number=1223"
    return "mathRequest";
  }
  return "standardRequest";
}
