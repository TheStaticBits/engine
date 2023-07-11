#include "util/sdlutil.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "util/log.h"

const bool util::initSDL(const uint32_t SDLFlags, const int IMGFlags)
{
    const bool result = (SDL_Init(SDLFlags) == 0 && IMG_Init(IMG_INIT_PNG) && TTF_Init() == 0);
    if (!result) logger::error("SDL failed to initialize");
    return result;
}

void util::quitSDL()
{
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}