#include "GoldbachStandardResponseHandler.hpp"

#include "HttpResponse.hpp"

GoldbachStandardResponseHandler::GoldbachStandardResponseHandler() {}

GoldbachStandardResponseHandler::~GoldbachStandardResponseHandler() {}

int GoldbachStandardResponseHandler::run() {
  // Start the forever loop to consume all the messages that arrive
  this->consumeForever();
  return EXIT_SUCCESS;
}

void GoldbachStandardResponseHandler::consume(const HttpRequest& data) {
  if (data.getMethod() == "GET" && data.getURI() == "/") {
    this->serveHomepage(data);
  }

  this->serveNotFound(data);
}

bool GoldbachStandardResponseHandler::serveHomepage(
    const HttpRequest& httpRequest) {
  HttpResponse httpResponse(httpRequest.getSocket());

  // Set HTTP response metadata (headers)
  httpResponse.setHeader("Server", "AsgardServer v1.0");
  httpResponse.setHeader("Content-type", "text/html; charset=ascii");

  // Build the body of the response
  std::string title = "Goldbach sums";
  httpResponse.body()
      << "<!DOCTYPE html>\n"
      << "<html lang=\"en\">\n"
      << "  <meta charset=\"ascii\"/>\n"
      << "  <title>" << title << "</title>\n"
      << "  <style>body {font-family: monospace}</style>\n"
      << "  <h1>" << title << "</h1>\n"
      << "  <form method=\"get\" action=\"/goldbach\">\n"
      << "    <label for=\"number\">Number</label>\n"
      << "    <input type=\"number\" name=\"number\" required/>\n"
      << "    <button type=\"submit\">Calculate</button>\n"
      << "  </form>\n"
      << "</html>\n";

  // Send the response to the client (user agent)
  return httpResponse.send();
}

bool GoldbachStandardResponseHandler::serveNotFound(
    const HttpRequest& httpRequest) {
  (void)httpRequest;

  HttpResponse httpResponse(httpRequest.getSocket());

  // Set HTTP response metadata (headers)
  httpResponse.setStatusCode(404);
  httpResponse.setHeader("Server", "AsgardServer v1.0");
  httpResponse.setHeader("Content-type", "text/html; charset=ascii");

  // Build the body of the response
  std::string title = "Not found";
  httpResponse.body()
      << "<!DOCTYPE html>\n"
      << "<html lang=\"en\">\n"
      << "  <meta charset=\"ascii\"/>\n"
      << "  <title>" << title << "</title>\n"
      << "  <style>body {font-family: monospace} h1 {color: red}</style>\n"
      << "  <h1>" << title << "</h1>\n"
      << "  <p>The requested resouce was not found in this server.</p>\n"
      << "  <hr><p><a href=\"/\">Homepage</a></p>\n"
      << "</html>\n";

  // Send the response to the client (user agent)
  return httpResponse.send();
}
