#include "animation.h"

#include "texture.h"
#include "window.h"
#include "util/vect.h"
#include "util/log.h"

Animation::Animation(Window& window, const std::string& path, const Vect<uint32_t> frameSize,
                     const float delay, const bool loop)
    : texture(window, path), frameSize(frameSize), delay(delay), loop(loop),
      frame(0), timer(0), finished(false), imgFrameDims(texture.getSourceSize() / frameSize)
{
    if (texture.getSourceSize() % frameSize != Vect<uint32_t>(0, 0))
        logger::warn("Animation at " + path + " - frame size does not divide evenly into texture size");
    
    texture.setSourceSize(frameSize);
    texture.setDestSize(frameSize * Texture::getScale());
}

void Animation::update(Window& window)
{
    if (finished && !loop) return;
    
    finished = false;
    timer += window.getDeltaTime();

    if (timer > delay)
    {
        // Reset timer, accounting for any amount of frames that were skipped
        while (timer > delay) 
        {
            timer -= delay;
            frame++;
        }
        
        // If the animation is finished
        if (frame > imgFrameDims.x * imgFrameDims.y) 
        {
            frame = 0;
            finished = true;
        }

        // set texture src pos
        texture.setSourcePos(Vect<int32_t>(frame % imgFrameDims.x, frame / imgFrameDims.x) * frameSize.cast<int32_t>());
    }
}

void Animation::render(Window& window)
{
    window.render(texture);
}