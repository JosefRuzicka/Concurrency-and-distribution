#ifndef GOLDBACHSTANDARRESPONSEHANDLER_H
#define GOLDBACHSTANDARRESPONSEHANDLER_H
#pragma once

#include "Consumer.hpp"
#include "HttpRequest.hpp"
class GoldbachStandardResponseHandler : public Consumer<HttpRequest> {
 private:
  bool serveHomepage(const HttpRequest& httpRequest);
  /// Sends a page for a non found resouce in this server
  bool serveNotFound(const HttpRequest& httpRequest);

 public:
  GoldbachStandardResponseHandler();
  ~GoldbachStandardResponseHandler();

  /**
Override this method to start the thread's tasks.
*/
  int run() override;
  /**
  Override this method to process any data extracted from the queue
  */
  void consume(const HttpRequest& data) override;
};
#endif