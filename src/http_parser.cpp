#include "http_parser.hpp"
#include <sstream>
#include <stdexcept>

HttpRequest HttpParser::parse_request(const std::string& raw_request) {
    HttpRequest req;
    std::istringstream iss(raw_request);
    std::string line;
    if (std::getline(iss, line)) {
        std::istringstream line_stream(line);
        line_stream >> req.method >> req.path >> req.version;
        if (req.method.empty() || req.path.empty() || req.version.empty()) {
            throw std::runtime_error("Invalid HTTP request");
        }
    } else {
        throw std::runtime_error("Empty HTTP request");
    }
    return req;
}

std::string HttpParser::build_response(const HttpResponse& response) {
    std::ostringstream oss;
    oss << "HTTP/1.1 " << response.status_code << " " << response.status_text << "\r\n";
    oss << "Content-Type: " << response.content_type << "\r\n";
    oss << "Content-Length: " << response.body.size() << "\r\n";
    oss << "\r\n";
    oss << response.body;
    return oss.str();
}