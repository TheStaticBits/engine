#pragma once

#include <iostream>

namespace logger {
    void output(const std::string& message);

    void info(const std::string& message);
    void warn(const std::string& message);
    void error(const std::string& message);
    void SDLError(const std::string& message);
    void IMGError(const std::string& message);
    void TTFError(const std::string& message);
}