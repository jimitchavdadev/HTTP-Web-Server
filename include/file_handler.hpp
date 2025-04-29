#ifndef FILE_HANDLER_HPP
#define FILE_HANDLER_HPP

#include <string>

class FileHandler {
public:
    FileHandler(const std::string& root_dir);
    std::string get_file_content(const std::string& path, std::string& content_type);

private:
    std::string root_dir_;
    std::string get_content_type(const std::string& path);
};

#endif // FILE_HANDLER_HPP