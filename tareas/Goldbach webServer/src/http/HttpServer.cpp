// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0

#include "HttpServer.hpp"

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string>

#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "Socket.hpp"

HttpServer::HttpServer() {
  this->serverClosed = false;
  this->requestHandler = new HttpRequestHandler();
}

HttpServer::~HttpServer() {}

void HttpServer::listenForever(const char* port) {
  return TcpServer::listenForever(port);
}

void HttpServer::stopListening() {
  this->serverClosed = true;
  for (size_t connection = 0; connection < this->connectionHandlers.size();
       connection++) {
    this->connections.push(Socket());
  }
  this->join();
}

void HttpServer::join() {
  for (size_t connection = 0; connection < this->connectionHandlers.size();
       connection++) {
    this->connectionHandlers[connection]->waitToFinish();
  }
}

void HttpServer::handleClientConnection(Socket& client) {
  this->connections.push(client);
}
void HttpServer::createHttpConnectionHandlers(size_t quantity) {
  this->connectionHandlers.resize(quantity);

  for (size_t index = 0; index < quantity; ++index) {
    this->connectionHandlers[index] = new HttpConnectionHandler();
    this->connectionHandlers[index]->setConsumingQueue(&this->connections);
    this->connectionHandlers[index]->setProducingQueue(&this->requests);
    this->connectionHandlers[index]->startThread();

    assert(this->connectionHandlers[index]);
  }
}
