#include "baseGame.h"

#include "util/log.h"

#ifdef __EMSCRIPTEN__
#include "emscripten.h"
#include "emscripten/html5.h"

void emIteration(void* gamePtr)
{
    BaseGame* game = (BaseGame*)gamePtr;
    game->iteration();
}

const char* emDestroy(int eventType, const void* reserved, void* gamePtr)
{
    BaseGame* game = (BaseGame*)gamePtr;
    game->destroy();
    return NULL;
}
#endif

const bool BaseGame::quit()
{
    logger::warn("Override BaseGame::quit() to implement quit conditions");
    return false;
}

void BaseGame::iteration()
{
    logger::info("Override BaseGame::iteration() to implement game logic");
}

void BaseGame::destroy()
{
    logger::info("Override BaseGame::destroy() to implement destroy/saving");
}

void BaseGame::start()
{
    logger::info("Starting game loop");

#ifdef __EMSCRIPTEN__
    logger::info("Emscripten setup");
    emscripten_set_beforeunload_callback(this, emDestroy);
    emscripten_set_main_loop_arg(emIteration, this, 0, 1);
#else
    logger::info("Desktop setup");
    while (!quit()) iteration();
    destroy();
#endif
}