#include "util/log.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <unordered_map>

const std::unordered_map<std::string, std::string> logger::colors = {
    { "green", "\033[32m" },
    { "yellow", "\033[33m" },
    { "red", "\033[31m" }
};

void logger::output(const std::string& message, const std::string& prefix)
{
#ifdef DEBUG_MODE
#ifdef __EMSCRIPTEN__
    std::cout << message << std::endl;
#else
    std::cout << prefix << message << "\033[0m" << std::endl;
#endif
#endif
}

void logger::info(const std::string& message)  { logger::output("[INFO] " + message); }
void logger::warn(const std::string& message)  { logger::output("[WARN] " + message, logger::colors.at("yellow")); }
void logger::error(const std::string& message) { logger::output("[ERROR] " + message, logger::colors.at("red")); }

void logger::errorThrow(const std::string& message) { 
    logger::output("[ERROR] " + message, logger::colors.at("red")); 
    throw std::runtime_error(message); 
}

void logger::SDLError(const std::string& message) { 
    logger::output("[SDL ERROR] " + message + " | " + SDL_GetError(), logger::colors.at("red")); 
}

void logger::IMGError(const std::string& message) { 
    logger::output("[IMG ERROR] " + message + " | " + IMG_GetError(), logger::colors.at("red")); 
}

void logger::TTFError(const std::string& message) {
    logger::output("[TTF ERROR] " + message + " | " + TTF_GetError(), logger::colors.at("red")); 
}