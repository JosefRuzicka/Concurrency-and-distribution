// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0

#ifndef HTTPMESSAGE_H
#define HTTPMESSAGE_H

#include <cctype>
#include <map>
#include <memory>
#include <sstream>
#include <string>

#include "Socket.hpp"
#include "common.hpp"

/// Case-insensitive comparing functor
/// Adapted from https://stackoverflow.com/a/1801913
struct IgnoreCaseLess {
  struct CompareChar {
    inline bool operator()(unsigned char c1, unsigned char c2) const {
      return ::tolower(c1) < ::tolower(c2);
    }
  };
  inline bool operator()(const std::string& s1, const std::string& s2) const {
    return std::lexicographical_compare(s1.begin(), s1.end(), s2.begin(),
                                        s2.end(), CompareChar());
  }
};

class HttpMessage {
 public:
  /// Objects of this class can be copied, but avoid innecesary copies
  DECLARE_RULE4(HttpMessage, default);
  /// Header metadata is represented as an associative array, but keys are
  /// case-insensitive according to the HTTP standard
  typedef std::map<std::string, std::string, IgnoreCaseLess> Headers;
  /// Line separators for HTTP messages is "\r\n"
  static const char* const lineSeparator;

 protected:
  /// Connection with client to receive or send HTTP data
  Socket socket;
  /// HTTP version, e.g: HTTP/1.0, HTTP/1.1
  /// TODO(you) Handle requests concurrently. Match HTTP version used by client
  /// TODO(any) HTTP/2.0 and newer versions are not supported
  std::string httpVersion = "HTTP/1.0";
  /// HTTP message headers (pairs key=value)
  Headers headers;
  /// Body contents is a shared buffer for all copies of this message object
  std::shared_ptr<std::stringstream> sharedBody;

 public:
  /// Constructor
  explicit HttpMessage(const Socket& socket);
  HttpMessage();
  /// Destructor
  ~HttpMessage();
  /// Get access to the connection with the client
  const Socket& getSocket() const;
  /// Get network address from the client
  NetworkAddress getNetworkAddress() const;
  /// Set a key=value header pair. That is, if the key does not exist, it is
  /// added to the message header, otherwise it is overwritten
  inline void setHeader(const std::string& key, const std::string& value) {
    this->headers[key] = value;
  }
  /// Get the value for a message header key. If the key does not exist, the
  /// default value will be returned
  std::string getHeader(const std::string& key,
                        const std::string& defaultvalue = "");
  /// Get read-only access to the body object
  inline const std::stringstream& body() const { return *this->sharedBody; }
  /// Get read/write access to the body contents
  inline std::stringstream& body() { return *this->sharedBody; }
  /// Return the length of the body in bytes
  inline size_t getBodyLength() const { return this->body().str().length(); }
  /// Tries to guess the type of content from the body
  /// @return A MIME type text, or empty string if body is empty
  std::string guessContentType() const;
  /// @return true if this object has the same message than the other's
  bool operator==(const HttpMessage& other) const;
};

#endif  // HTTPMESSAGE_H
