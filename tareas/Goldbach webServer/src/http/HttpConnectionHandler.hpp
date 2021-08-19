// Created by Samantha Romero.

#ifndef HTTPCONNECTIONHANDLER_H
#define HTTPCONNECTIONHANDLER_H

#include <GoldbachOrder.hpp>

#include "Assembler.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
class HttpConnectionHandler : public Assembler<Socket, HttpRequest> {
  DISABLE_COPY(HttpConnectionHandler);

 private:
  // Queue where the HttpConnectionHandler wiil put th

 public:
  /**
   * @brief Constructor.
   * @param producer: Pointer to a producer in order to being able to call its
   * functions.
   */
  explicit HttpConnectionHandler();
  /**
  Override this method to start the thread's tasks.
  */
  int run() override;
  /**
  Override this method to process any data extracted from the queue
  */
  void consume(const Socket& data) override;
};

#endif  // HTTPCONNECTIONHANDLER_H