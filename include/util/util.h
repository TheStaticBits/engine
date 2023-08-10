#pragma once

#include <iostream>
#include <nlohmann/json.hpp>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

namespace util
{
    const bool initSDL(const uint32_t SDLFlags, const int IMGFlags);
    void quitSDL();
    const SDL_Color vecToColor(const std::vector<uint8_t>& color);
    const nlohmann::json loadJson(const std::string& path);
}