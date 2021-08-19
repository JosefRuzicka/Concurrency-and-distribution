// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0

#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include "HttpConnectionHandler.hpp"
#include "HttpRequest.hpp"
#include "HttpRequestHandler.hpp"
#include "HttpResponse.hpp"
#include "TcpServer.hpp"

class HttpServer : public TcpServer {
  DISABLE_COPY(HttpServer);

 protected:
  /// Lookup criteria for searching network information about this host
  struct addrinfo hints;
  Queue<Socket> connections;
  Queue<HttpRequest> requests;
  HttpRequestHandler* requestHandler;
  std::vector<HttpConnectionHandler*> connectionHandlers;
  bool serverClosed;

 public:
  /// Constructor
  HttpServer();
  /// Destructor
  ~HttpServer();
  /// Infinetelly listen for client connection requests and accept all of them.
  /// For each accepted connection request, the virtual onConnectionAccepted()
  /// will be called. Inherited classes must override that method
  void listenForever(const char* port);

  /**
   * @brief: Stop listening for client connection requests and put threads to
   * sleep by filling the consuming queue with empty sockets recognized as stop
   * conditions.
   *
   */
  void stopListening();

  /**
   * @brief: Waits for every HttpConnectionHandler thread to finish its task.
   */
  void join();

 protected:
  void createHttpConnectionHandlers(size_t quantity);
  /// This method is called each time a client connection request is accepted.
  void handleClientConnection(Socket& client) override;
};

#endif  // HTTPSERVER_H
