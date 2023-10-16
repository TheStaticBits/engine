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

std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> Texture::textures = {};
uint32_t Texture::scale = 1; // Default render scale

Texture::Texture(Window& window, const std::string& path, const uint32_t overrideScale, const bool shared)
    : texture(getImage(window, path, shared)), path(path)
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

const std::shared_ptr<SDL_Texture> Texture::getImage(Window& window, const std::string& path, const bool shared)
{
    if (!shared) return loadImage(window, path);

    // If the texture has not been created already, load it
    if (textures.find(path) == textures.end())
        textures[path] = loadImage(window, path);
    
    return textures.at(path);
}

const std::shared_ptr<SDL_Texture> Texture::loadImage(Window& window, const std::string& path)
{
    return std::shared_ptr<SDL_Texture>(window.loadTexture(path), SDLTextureDeleter);
}

void Texture::initSizes(const uint32_t overrideScale)
{
    srcSize = Texture::getSize(texture.get()).cast<uint32_t>();
    
    if (overrideScale != 0)
        destSize = srcSize * overrideScale;
    else
        destSize = srcSize * scale;
}

void Texture::modColor(const std::vector<uint8_t>& color)
{
    if (SDL_SetTextureColorMod(texture.get(), color[0], color[1], color[2]) != 0)
        logger::error("Failed to set texture color mod");
}

const Vect<int32_t> Texture::getSize(SDL_Texture* texture)
{
    Vect<int32_t> size;
    
    if (SDL_QueryTexture(texture, nullptr, nullptr, &size.x, &size.y) != 0)
        logger::error("Failed to query for texture size");

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