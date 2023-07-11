#include "texture.h"

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "window.h"
#include "util/log.h"

uint32_t Texture::scale = 1; // Default render scale

Texture::Texture(Window& window, const std::string& path)
    : texture(window.loadTexture(path)),
      size(Texture::getSize(texture).cast<uint32_t>()),
      renderSize(size * scale), path(path)
{
    
}

Texture::~Texture()
{
    SDL_DestroyTexture(texture);
    logger::info("Destroyed texture at " + path);
}

const Vect<int32_t> Texture::getSize(SDL_Texture* texture)
{
    Vect<int32_t> size;
    SDL_QueryTexture(texture, nullptr, nullptr, &size.x, &size.y);
    return size.cast<int32_t>();
}

void Texture::setScale(const uint32_t scale)
{
    Texture::scale = scale;
}