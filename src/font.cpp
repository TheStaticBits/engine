#include "font.h"

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "util/log.h"
#include "texture.h"
#include "window.h"

std::vector<Font> Font::fonts;

// Prevents duplicate font objects from being created
Font* Font::getFont(const std::string& path, const uint32_t size)
{
    for (Font& font : fonts)
        if (font.path == path && font.size == size) 
            return &font;

    // If the font doesn't exist, create it
    fonts.emplace_back(path, size);
    return &(fonts.back());
}

void Font::destroyFont(Font* font)
{
    for (auto it = fonts.begin(); it != fonts.end(); ++it)
        if (&(*it) == font)
        {
            fonts.erase(it);
            return;
        }
    
    logger::warn("Failed to delete font at " + font->getPath() + " with size " + std::to_string(font->getSize()) + " pixels");
}

void Font::destroyAll()
{
    fonts.clear();
}

Font::Font(const std::string& path, const uint32_t size)
    : font(nullptr), path(path), size(size)
{
    font = TTF_OpenFont(path.c_str(), size);

    if (font == nullptr) logger::TTFError("Failed to load font at " + path);
    else logger::info("Loaded font at " + path);
}

Font::~Font()
{
    destroy();
}

void Font::destroy()
{
    if (font == nullptr) return;
    TTF_CloseFont(font);
    font = nullptr;
    logger::info("Destroyed font at " + path + " with size " + std::to_string(size) + " pixels");
}

Font::Font(Font&& other)
    : font(other.font), path(other.path), size(other.size)
{
    other.font = nullptr;
}

Font& Font::operator=(Font&& other)
{
    destroy();

    font = other.font;
    path = other.path;
    size = other.size;

    other.font = nullptr;
    return *this;
}

SDL_Texture* Font::loadText(Window& window, const std::string& text, SDL_Color color)
{
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture* texture = window.surfToTex(surface);
    return texture;
}