#include "util/log.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

void logger::output(const std::string& message)
{
#ifdef DEBUG_MODE
    std::cout << message << std::endl;
#endif
}

void logger::info(const std::string& message) { logger::output("[INFO] " + message); }
void logger::warn(const std::string& message) { logger::output("[WARN] " + message); }
void logger::error(const std::string& message) { logger::output("[ERROR] " + message); }
void logger::errorThrow(const std::string& message) { logger::output("[ERROR] " + message); throw std::runtime_error(message); }
void logger::SDLError(const std::string& message) { logger::output("[SDL ERROR] " + message + " | " + SDL_GetError()); }
void logger::IMGError(const std::string& message) { logger::output("[IMG ERROR] " + message + " | " + IMG_GetError()); }
void logger::TTFError(const std::string& message) { logger::output("[TTF ERROR] " + message + " | " + TTF_GetError()); }
