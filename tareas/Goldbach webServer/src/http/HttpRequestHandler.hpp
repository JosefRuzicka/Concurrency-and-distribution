#ifndef HTTPREQUESTHANDLER_H
#define HTTPREQUESTHANDLER_H
#include "Dispatcher.hpp"
#include "HttpRequest.hpp"

class HttpRequestHandler : public Dispatcher<std::string, HttpRequest> {
 private:
 public:
  HttpRequestHandler();
  ~HttpRequestHandler();

  int run() override;
  /// This method extracts the key from a data stored in the fromQueue
  std::string extractKey(const HttpRequest& data) const override;
};
#endif