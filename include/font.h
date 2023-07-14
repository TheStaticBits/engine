#pragma once

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class Texture;
class Window;

class Font
{
public:
    static Font& getFont(const std::string& path, const uint32_t size);

    // Do not call constructor directly, use getFont() instead
    Font(const std::string& path, const uint32_t size); 
    Font(Font&&);

    Font(const Font& other) = delete;
    Font& operator=(const Font&) = delete;
    Font& operator=(Font&&) = delete;

    ~Font();
    
    SDL_Texture* loadText(Window& window, const std::string& text, SDL_Color color);

    // Getters
    inline TTF_Font* getFont() const { return font; }
    inline const std::string& getPath() const { return path; }
    inline const uint32_t getSize() const { return size; }

private:
    static std::vector<Font> fonts;

    TTF_Font* font;

    const std::string path;
    const uint32_t size;
};