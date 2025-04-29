#ifndef HTTP_PARSER_HPP
#define HTTP_PARSER_HPP

#include <string>

struct HttpRequest {
    std::string method;
    std::string path;
    std::string version;
};

struct HttpResponse {
    int status_code;
    std::string status_text;
    std::string content_type;
    std::string body;
};

class HttpParser {
public:
    HttpRequest parse_request(const std::string& raw_request);
    std::string build_response(const HttpResponse& response);
};

#endif // HTTP_PARSER_HPP