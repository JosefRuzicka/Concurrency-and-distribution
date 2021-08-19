// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0
// Serial web server's initial code for parallelization

//#ifdef WEBSERVER

#include <csignal>
#include <iostream>

#include "WebServer.hpp"

// Adapted from: https://www.geeksforgeeks.org/c-signal-handling/
void signal_handler(int signal_num) {
  std::cout << "\nServer Closing down. Signal number: " << signal_num
            << std::endl;
  // Stop threads
  WebServer::getInstance()->stopListening();
  // WebServer::getInstance()->stopCalculators();

  // terminate program
  exit(signal_num);
}

int main(int argc, char* argv[]) {
  signal(SIGTERM, signal_handler);
  signal(SIGINT, signal_handler);
  WebServer* asgardServer = WebServer::getInstance();
  return asgardServer->start(argc, argv);
}

//#endif  // WEBSERVER
