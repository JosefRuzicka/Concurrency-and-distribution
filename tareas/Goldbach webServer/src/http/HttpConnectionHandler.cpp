
#include "HttpConnectionHandler.hpp"

using namespace std;

#include <cassert>
#include <iostream>
#include <regex>
#include <stdexcept>
#include <string>

#include "GoldbachWebApp.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "NetworkAddress.hpp"
#include "Socket.hpp"

HttpConnectionHandler::HttpConnectionHandler() {}

int HttpConnectionHandler::run() {
  // Start the forever loop to consume all the messages that arrive
  this->consumeForever();
  return EXIT_SUCCESS;
}

/**
 * @brief Routes a socket towards the WebServer in order for it to be worked
 * upon.
 * @param data: Socket to be handled.
 */
void HttpConnectionHandler::consume(const Socket& data) {
  // While the same client asks for HTTP requests in the same connection

  // Create an object that parses the HTTP request from the socket
  // creates a copy of the socket (client)
  HttpRequest httpRequest(data);

  // If the request is not valid or an error happened
  if (!httpRequest.parse()) {
    return;
  }

  // const bool handled = this->handleHttpRequest(httpRequest, httpResponse);
  this->produce(httpRequest);
}
