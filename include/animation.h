#pragma once

#include "texture.h"
#include "window.h"
#include "util/vect.h"
#include "util/log.h"

class Animation
{
public:
    Animation(Window& window, const std::string& path, const Vect<uint32_t> frameSize,
              const float delay, const bool loop = true, const uint32_t frames = 0);
    
    void update(Window& window);
    void render(Window& window);

    // Getters
    inline Texture& getTex() { return texture; }
    inline const bool isFinished() const { return finished; }
    inline void continueAnim() { finished = false; }

private:
    Texture texture;

    Vect<uint32_t> frameSize;
    const float delay;
    const bool loop;

    uint32_t frame;
    uint32_t frameCount;
    float timer;
    bool finished;
    Vect<uint32_t> imgFrameDims; // amount of times the frame fits into the image vertically and horizontally
};