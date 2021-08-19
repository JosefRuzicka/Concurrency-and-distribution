#include "GoldbachMathOrderResponseHandler.hpp"

#include "GoldbachWebApp.hpp"
#include "HttpResponse.hpp"

GoldbachMathOrderResponseHandler::GoldbachMathOrderResponseHandler() {}

GoldbachMathOrderResponseHandler::~GoldbachMathOrderResponseHandler() {}

int GoldbachMathOrderResponseHandler::run() {
  // Start the forever loop to consume all the messages that arrive
  this->consumeForever();
  return EXIT_SUCCESS;
}

void GoldbachMathOrderResponseHandler::consume(
    const GoldbachProccessedMathOrder& data) {
  HttpResponse http_response(data.getSocket());

  // Set HTTP response metadata (headers)
  http_response.setHeader("Server", "AsgardServer v2.0");
  http_response.setHeader("Content-type", "text/html; charset=ascii");

  std::string processedNumbers =
      GoldbachWebApp::assemblyHttpResponseBody(data.getGoldbachUnits());
  // Build the body of the response
  std::string title = "Goldbach sums";
  http_response.body()
      << "<!DOCTYPE html>\n"
      << "<html lang=\"en\">\n"
      << "  <meta charset=\"ascii\"/>\n"
      << "  <title>" << title << "</title>\n"
      << "  <style>body {font-family: monospace} .err {color: red}</style>\n"
      << "  <h1>" << title << "</h1>\n"
      << "  <h2>" << processedNumbers << "</h2>\n"

      << "  </ol>\n"
      << "  <hr><p><a href=\"/\">Back</a></p>\n"
      << "</html>\n";

  // Send the response to the client (user agent)
  http_response.send();
}
