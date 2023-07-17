#include "texture.h"

#include <iostream>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "window.h"
#include "util/log.h"

void SDLTextureDeleter(SDL_Texture* texture)
{
    SDL_DestroyTexture(texture);
    logger::info("Destroyed instance of SDL_Texture");
}

uint32_t Texture::scale = 1; // Default render scale

Texture::Texture(Window& window, const std::string& path, const uint32_t overrideScale)
    : texture(window.loadTexture(path), SDLTextureDeleter), path(path)
{
    initSizes(overrideScale);
}

Texture::Texture(SDL_Texture* tex, const uint32_t overrideScale)
    : texture(tex, SDLTextureDeleter), path("[no path]")
{
    initSizes(overrideScale);
}

Texture::Texture()
    : texture(nullptr), path("[uninitialized]")
{
    
}

Texture::~Texture()
{
    logger::info("Destroying instance of texture at " + path);
}

void Texture::initSizes(const uint32_t overrideScale)
{
    srcSize = Texture::getSize(texture.get()).cast<uint32_t>();
    
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