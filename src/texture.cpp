#include "texture.h"

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "window.h"
#include "util/log.h"

uint32_t Texture::scale = 1; // Default render scale

Texture::Texture(Window& window, const std::string& path, const uint32_t overrideScale)
    : texture(window.loadTexture(path)), path(path)
{
    initSizes(overrideScale);
}

Texture::Texture(SDL_Texture* texture, const uint32_t overrideScale)
    : texture(texture)
{
    initSizes(overrideScale);
}

Texture::~Texture()
{
    SDL_DestroyTexture(texture);
    logger::info("Destroyed texture at " + path);
}

void Texture::initSizes(const uint32_t overrideScale)
{
    srcSize = Texture::getSize(texture).cast<uint32_t>();
    
    if (overrideScale != 0)
        destSize = srcSize * overrideScale;
    else
        destSize = srcSize * scale;
}

const Vect<int32_t> Texture::getSize(SDL_Texture* texture)
{
    Vect<int32_t> size;
    SDL_QueryTexture(texture, nullptr, nullptr, &size.x, &size.y);
    return size.cast<int32_t>();
}

const Vect<int32_t> Texture::getSize(Texture& texture)
{
    return Texture::getSize(texture.getTexture());
}

void Texture::setScale(const uint32_t scale)
{
    Texture::scale = scale;
}