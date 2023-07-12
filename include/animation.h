#pragma once

#include "texture.h"
#include "window.h"
#include "util/vect.h"
#include "util/log.h"

class Animation
{
public:
    Animation(Window& window, const std::string& path, const Vect<uint32_t> frameSize,
              const float delay, const bool loop = true);
    
    void update(Window& window);
    void render(Window& window);

    inline const bool isFinished() const { return finished; }
    inline void continueAnim() { finished = false; }

private:
    Texture texture;

    const Vect<uint32_t> frameSize;
    const float delay;
    const bool loop;

    uint32_t frame;
    float timer;
    bool finished;
    Vect<uint32_t> imgFrameDims; // amount of times the frame fits into the image vertically and horizontally
};