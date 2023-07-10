#include "window.h"

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "util/vect.h"
#include "util/log.h"
#include "texture.h"

// Static variable default definitions:
// Allows keys
std::unordered_map<SDL_Keycode, Window::KeyState> Window::keys = {};
std::vector<SDL_Keycode> Window::allowedKeys = {};
const std::vector<uint8_t> Window::defaultClearColor = { 0, 0, 0, 255 };

// Mouse
Vect<int32_t> Window::mousePos = { 0, 0 };
std::unordered_map<uint8_t, Window::KeyState> Window::mouseState = {}; // SDL_BUTTON_LEFT, SDL_BUTTON_RIGHT, SDL_BUTTON_MIDDLE

// Focused windows
Window* Window::keyFocusedWindow = nullptr;
Window* Window::mouseFocusedWindow = nullptr;


Window::Window(const Vect<uint32_t>& size, const std::string& title, const bool vsync, const bool outputFPS)
    : window(nullptr), renderer(nullptr),
      deltaTime(0), lastFrame(SDL_GetTicks()), outputFPS(outputFPS), 
      closed(false), destroyed(false), size(size)
{
    createSDLWindow(title, vsync);
}

void Window::createSDLWindow(const std::string& title, const bool vsync)
{
    // SDL flags
	int flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE;
    if (vsync) flags |= SDL_RENDERER_PRESENTVSYNC; // Vsync

    // init window and renderer
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, size.x, size.y, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, flags);

    if (window == nullptr) logger::error("Failed to create window");
    if (renderer == nullptr) logger::error("Failed to create renderer");
    else resetDrawColor(); // Renderer created successfully, set draw color
}

void Window::destroy()
{
    if (destroyed) return;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    logger::info("Destroyed window");
    destroyed = true;
}

void Window::setAllowedKeys(const std::vector<SDL_Keycode>& keys)
{
    Window::allowedKeys = keys;
}

void Window::presentFrame()
{
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);

    // Calculate deltatime (time in seconds since last frame)
    uint64_t currentFrame = SDL_GetTicks64();

    // Print average fps every second
    if (outputFPS && (currentFrame % 1000) < (lastFrame % 1000))
    {
        // add together all deltatimes over the last second
        float totalDeltaTime = 0;
        for (const uint64_t frame : deltaTimes) totalDeltaTime += frame;
        const float fps = static_cast<float>(deltaTimes.size()) / totalDeltaTime;
        logger::info("FPS: " + std::to_string(fps));
    }

    deltaTime = (currentFrame - lastFrame) / 1000.0f;
    lastFrame = currentFrame;
}

void Window::updateKeyStates()
{
    for (auto& key : keys)
    {
        if (key.second == PRESSED) key.second = HELD; // Move to HELD state
        else if (key.second == RELEASED) key.second = NONE; // Move to NONE state
    }
}

void Window::updateMouse()
{
    SDL_GetMouseState(&mousePos.x, &mousePos.y);

    for (auto& button : mouseState)
    {
        if (button.second == PRESSED) button.second = HELD;
        else if (button.second == RELEASED) button.second = NONE;
    }
}

void Window::handleInputs(std::vector<Window*>& windows)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_WINDOWEVENT) 
            handleWindowEvent(event, windows);

        else if (event.type == SDL_MOUSEBUTTONDOWN) 
            mouseState[event.button.button] = PRESSED;
        else if (event.type == SDL_MOUSEBUTTONUP) 
            mouseState[event.button.button] = RELEASED;
        
        else if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) 
            handleKey(event.key.keysym.sym, event.type);
    }
}

void Window::handleInputs(std::vector<Window>& windows)
{
    std::vector<Window*> windowPtrs = {};

    for (auto& window : windows) 
        windowPtrs.push_back(&window);
    
    handleInputs(windowPtrs);
}

void Window::handleInputs(Window& window)
{
    std::vector<Window*> windows(1, &window);
    handleInputs(windows);
}

void Window::handleWindowEvent(const SDL_Event& event, std::vector<Window*>& windows)
{
    // Handles windows coming in and out of focus
    switch (event.window.event) {
    case SDL_WINDOWEVENT_FOCUS_GAINED:
        keyFocusedWindow = find(event.window.windowID, windows); // window focused
        break;
    case SDL_WINDOWEVENT_ENTER:
        mouseFocusedWindow = find(event.window.windowID, windows); // mouse hovered
        break;
        
    case SDL_WINDOWEVENT_FOCUS_LOST:
        keyFocusedWindow = nullptr; // window unfocused
        break;
    case SDL_WINDOWEVENT_LEAVE:
        mouseFocusedWindow = nullptr; // mouse left window
        break;
        
    case SDL_WINDOWEVENT_CLOSE:
        logger::info("Window closed");
        keyFocusedWindow->closed = true; // window closed
        break;
    }
}

Window* Window::find(const uint32_t id, std::vector<Window*>& windows)
{
    if (windows.size() == 1) 
        return windows[0];

    for (auto& window : windows) 
        if (window->getID() == id) 
            return window;
    
    logger::error("Failed to find window from id");
    return windows[0];
}

void Window::handleKey(const SDL_Keycode& key, const uint32_t type)
{
    if (std::find(allowedKeys.begin(), allowedKeys.end(), key) == allowedKeys.end())
        return;
    
    if (type == SDL_KEYDOWN) keys[key] = PRESSED;
    else if (type == SDL_KEYUP) keys[key] = RELEASED;
}

[[nodiscard]] SDL_Texture* Window::loadTexture(const std::string& path)
{
    SDL_Texture* texture = IMG_LoadTexture(renderer, path.c_str());
    if (texture == nullptr) logger::IMGError("Failed to load texture: " + path);
    return texture;
}

void Window::render(Texture& texture)
{
    SDL_Rect srcRect = texture.getOriginalRect();
    SDL_Rect dstRect = texture.getRect();
    SDL_RenderCopy(renderer, texture.getTexture(), &srcRect, &dstRect);
}

void Window::render(const SDL_Rect& rect, const std::vector<uint8_t>& color)
{
    setDrawColor(color);
    SDL_RenderFillRect(renderer, &rect);
    resetDrawColor();
}

void Window::setDrawColor(const std::vector<uint8_t>& color)
{
    SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], color[3]);
}

void Window::resetDrawColor()
{
    setDrawColor(defaultClearColor);
}

void Window::setDrawTarget(Texture& texture)
{
    SDL_SetRenderTarget(renderer, texture.getTexture());
}

void Window::resetDrawTarget()
{
    SDL_SetRenderTarget(renderer, nullptr);
}

const bool Window::keyHeld(const SDL_Keycode& key)
{
    const Window::KeyState state = keys[key];
    return state == HELD || state == PRESSED;
}

const bool Window::keyPressed(const SDL_Keycode& key)
{
    return keys[key] == PRESSED;
}

const bool Window::keyReleased(const SDL_Keycode& key)
{
    return keys[key] == RELEASED;
}

const bool Window::mouseHeld(const uint8_t& button)
{
    Window::KeyState state = mouseState[button];
    return state == HELD || state == PRESSED;
}

const bool Window::mousePressed(const uint8_t& button)
{
    return mouseState[button] == PRESSED;
}

const bool Window::mouseReleased(const uint8_t& button)
{
    return mouseState[button] == RELEASED;
}