#pragma once

#include <iostream>
#include <unordered_map>

namespace logger {
    extern const std::unordered_map<std::string, std::string> colors;

    void output(const std::string& message, const std::string& prefix="");
    void outputGreen(const std::string& message);
    void outputYellow(const std::string& message);
    void outputRed(const std::string& message);

    void info(const std::string& message);
    void warn(const std::string& message);
    void error(const std::string& message);
    void errorThrow(const std::string& message);
    void SDLError(const std::string& message);
    void IMGError(const std::string& message);
    void TTFError(const std::string& message);
}