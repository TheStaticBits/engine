#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "window.h"
#include "util/vect.h"

class Texture
{
public:
    Texture(Window& window, const std::string& path, const uint32_t overrideScale=0);
    Texture(SDL_Texture* texture, const uint32_t overrideScale=0);
    Texture();

    Texture(Texture&&);
    Texture& operator=(Texture&&);

    Texture(const Texture& other) = delete;
    Texture& operator=(const Texture&) = delete;
    
    ~Texture();
    void destroy();

    void initSizes(const uint32_t overrideScale);

    // Getters
    static inline const uint32_t getScale() { return scale; }

    static const Vect<int32_t> getSize(SDL_Texture* texture);
    static const Vect<int32_t> getSize(Texture& texture);

    inline SDL_Texture* getTexture() const { return texture; }
    inline const Vect<uint32_t>& getDestSize() const { return destSize; }
    inline const Vect<uint32_t>& getSourceSize() const { return srcSize; }
    inline const Vect<int32_t>& getDestPos() const { return destPos; }
    inline const Vect<int32_t>& getSourcePos() const { return srcPos; }
    inline const SDL_Rect getDestRect() const { return VectToRect(destPos, destSize); }
    inline const SDL_Rect getSourceRect() const { return VectToRect(srcPos, srcSize); }
    
    // Setters
    static void setScale(const uint32_t scale);

    inline const void setSourcePos(const Vect<int32_t>& pos) { srcPos = pos; }
    inline const void setSourceSize(const Vect<uint32_t>& size) { srcSize = size; }
    inline const void setDestPos(const Vect<int32_t>& pos) { destPos = pos; }
    inline const void setDestSize(const Vect<uint32_t>& size) { destSize = size; }

private:
    static uint32_t scale; // Render scale

    SDL_Texture* texture;
    std::string path;

    Vect<int32_t> srcPos;
    Vect<uint32_t> srcSize;
    Vect<int32_t> destPos;
    Vect<uint32_t> destSize;
};