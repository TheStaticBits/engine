#pragma once

#include <iostream>
#include <memory> // shared_ptr
#include <unordered_map>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "window.h"
#include "util/vect.h"
#include "util/util.h"

class Texture
{
public:
    Texture(Window& window, const std::string& path, const uint32_t overrideScale=0, const bool shared=true);
    Texture(SDL_Texture* tex, const uint32_t overrideScale=0);
    Texture();

    ~Texture();

    const std::shared_ptr<SDL_Texture> getImage(Window& window, const std::string& path, const bool shared);
    const std::shared_ptr<SDL_Texture> loadImage(Window& window, const std::string& path);

    void initSizes(const uint32_t overrideScale);

    void modColor(const std::vector<uint8_t>& color);

    void setBlendMode(const SDL_BlendMode mode);
    void resetBlendMode();

    // Getters
    static inline const uint32_t getScale() { return scale; }

    static const Vect<int32_t> getSize(SDL_Texture* texture);
    static const Vect<int32_t> getSize(Texture& texture);

    const Vect<uint32_t> getInitialDestSize(const uint32_t overrideScale=0) const;
    
    inline SDL_Texture* getTexture() const { return texture.get(); }
    inline const std::string& getPath() const { return path; }

    inline const Vect<uint32_t>& getInitialSrcSize() const { return initialSrcSize; }
    inline const Vect<uint32_t>& getDestSize() const { return destSize; }
    inline const Vect<uint32_t>& getSourceSize() const { return srcSize; }
    inline const Vect<int32_t>& getDestPos() const { return destPos; }
    inline const Vect<int32_t>& getSourcePos() const { return srcPos; }

    inline const SDL_Rect getDestRect() const { return util::vectToRect(destPos, destSize); }
    inline const SDL_Rect getSourceRect() const { return util::vectToRect(srcPos, srcSize); }
    
    // Setters
    static void setScale(const uint32_t scale);

    inline const void setSourcePos(const Vect<int32_t>& pos) { srcPos = pos; }
    inline const void setSourceSize(const Vect<uint32_t>& size) { srcSize = size; }
    inline const void setDestPos(const Vect<int32_t>& pos) { destPos = pos; }
    inline const void setDestSize(const Vect<uint32_t>& size) { destSize = size; }

private:
    static uint32_t scale; // Render scale

    static std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> textures;

    std::shared_ptr<SDL_Texture> texture;
    std::string path;

    Vect<int32_t> srcPos;
    Vect<uint32_t> initialSrcSize;
    Vect<uint32_t> srcSize;
    Vect<int32_t> destPos;
    Vect<uint32_t> destSize;
};