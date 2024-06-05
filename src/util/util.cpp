#include "util/util.h"

#include <fstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "util/log.h"
#include "font.h"

const bool util::initSDL(const uint32_t SDLFlags, const int IMGFlags)
{
    const bool result = (SDL_Init(SDLFlags) == 0 && IMG_Init(IMG_INIT_PNG) && TTF_Init() == 0);
    if (!result) logger::error("SDL failed to initialize");
    return result;
}

void util::quitSDL()
{
    Font::destroyAll(); // cleanup

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

const SDL_Color util::vecToColor(const std::vector<uint8_t>& color)
{
    uint8_t fourth = ((color.size() >= 4) ? color[3] : 255);
    return { color[0], color[1], color[2], fourth };
}


const std::vector<uint8_t> util::colorToVec(const SDL_Color& color)
{
    return { color.r, color.g, color.b, color.a };
}

const nlohmann::json util::loadJson(const std::string& path)
{
    std::ifstream file(path);

    if (file.is_open())
    {
        logger::info("Successfully loaded " + path);
        return nlohmann::json::parse(file, nullptr, true, true); // Allow comments
    }

    logger::error("Failed to open JSON file (returning empty JSON): " + path);
    return nlohmann::json();
}