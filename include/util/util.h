#pragma once

#include <iostream>
#include <nlohmann/json.hpp>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "util/vect.h"

namespace util
{
    const bool initSDL(const uint32_t SDLFlags, const int IMGFlags);
    void quitSDL();
    const SDL_Color vecToColor(const std::vector<uint8_t>& color);
    const nlohmann::json loadJson(const std::string& path);
    
    template <class T, class U>
    inline const SDL_Rect vectToRect(const Vect<T>& position, const Vect<U>& size)
    {
        SDL_Rect rect;
        rect.x = static_cast<int>(position.x);
        rect.y = static_cast<int>(position.y);
        rect.w = static_cast<int>(size.x);
        rect.h = static_cast<int>(size.y);
        return rect;
    }
}