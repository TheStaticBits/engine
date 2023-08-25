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

    template <class T>
    inline const std::vector<T> jsonToVector(const nlohmann::json& json)
    {
        std::vector<T> result;
        for (const auto& element : json)
            result.push_back(element.get<T>());
        return result;
    }

    template <class T>
    inline const bool collidePoint(const Vect<T>& point, const SDL_Rect rect)
    {
        return (point.x >= rect.x && point.x <= rect.x + rect.w &&
                point.y >= rect.y && point.y <= rect.y + rect.h);
    }

    inline const bool collideRect(const SDL_Rect& rect1, const SDL_Rect& rect2)
    {
        return (rect1.x < rect2.x + rect2.w &&
                rect1.y < rect2.y + rect2.h &&
                rect2.x < rect1.x + rect1.w &&
                rect2.y < rect1.y + rect1.h);
    }
}