#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "window.h"
#include "util/vect.h"

class Texture
{
public:
    Texture(Window& window, const std::string& path);

    Texture(const Texture&) = delete;
    Texture(Texture&&) = delete;
    Texture& operator=(const Texture&) = delete;
    Texture& operator=(Texture&&) = delete;
    
    ~Texture();

    // Getters
    static const Vect<int32_t> getSize(SDL_Texture* texture);

    inline SDL_Texture* getTexture() const { return texture; }
    inline const Vect<uint32_t>& getSize() const { return renderSize; }
    inline const Vect<uint32_t>& getOriginalSize() const { return size; }
    inline const Vect<int32_t>& getPos() const { return position; }
    inline const SDL_Rect getRect() const { return VectToRect(position, renderSize); }
    inline const SDL_Rect getOriginalRect() const { return VectToRect(position, size); }
    
    // Setters
    static void setScale(const uint32_t scale);

private:
    static uint32_t scale; // Render scale

    SDL_Texture* texture;
    const Vect<uint32_t> size;
    const Vect<uint32_t> renderSize;
    const Vect<int32_t> position;

#ifdef DEBUG_MODE
    const std::string& path;
#endif
};