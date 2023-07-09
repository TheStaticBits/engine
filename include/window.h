#pragma once

#include <iostream>
#include <unordered_map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "util/vect.h"
class Texture;

class Window
{
public:
    // Key states (also used for mouse events):
    // HELD represents a key being held for more than 2 frames,
    // PRESSED represents a key being pressed for the first time,
    // RELEASED represents a key being released for the first time.
    enum KeyState { HELD, PRESSED, RELEASED, NONE };

public: // Public methods
    Window(const Vect<uint32_t>& size, const std::string& title, const bool vsync);
    void createSDLWindow(const std::string& title, const bool vsync);
    void destroy();

    static void setAllowedKeys(const std::vector<SDL_Keycode>& keys);

    // Call these every frame
    void presentFrame();
    void updateInputs();
    static void handleInputs(std::vector<Window*>& windows); // once per frame no matter the amount of windows
    static void handleInputs(std::vector<Window>& window);
    static void handleInputs(Window& window); // For single-window applications
    
    [[nodiscard]] SDL_Texture* loadTexture(const std::string& path);

    // Draw methods
    void render(Texture& texture);
    void render(const SDL_Rect& rect, const std::vector<uint8_t>& color);

    void setDrawColor(const std::vector<uint8_t>& color);
    void resetDrawColor();

    void setDrawTarget(Texture& texture);
    void resetDrawTarget();

    // Getters
    inline const float getDeltaTime() const { return deltaTime; }
    inline const bool isClosed() const { return closed; }

    const bool keyHeld(const SDL_Keycode& key) const; // If the key is held
    const bool keyPressed(const SDL_Keycode& key) const; // The frame on which the key was pressed
    const bool keyReleased(const SDL_Keycode& key) const; // The frame on which the key was released

    const bool mouseHeld(const uint8_t& key) const;
    const bool mousePressed(const uint8_t& key) const;
    const bool mouseReleased(const uint8_t& key) const;

    inline const Vect<int32_t>& getMousePos() const { return mousePos; }

private: // Private methods
    void updateKeys();
    void handleKey(const SDL_Keycode& key, const uint32_t type);

    void updateMousePos();

    static void handleWindowEvent(const SDL_Event& event, std::vector<Window*>& windows);

    // interface methods with static methods
    inline uint32_t getID() const { return SDL_GetWindowID(window); }
    static Window* find(const uint32_t id, std::vector<Window*>& windows);

private: // Vars
    static std::vector<SDL_Keycode> allowedKeys; // keys that are tracked
    const static std::vector<uint8_t> clearColor; // clear color/default draw color

    static Window* keyFocusedWindow;
    static Window* mouseFocusedWindow;

    SDL_Window* window;
    SDL_Renderer* renderer;

    float deltaTime;
    uint64_t lastFrame;

    bool closed;
    bool destroyed;
    const Vect<uint32_t> size;

    // Key states
    std::unordered_map<SDL_Keycode, Window::KeyState> keys;

    // Mouse
    Vect<int32_t> mousePos;
    std::unordered_map<uint8_t, Window::KeyState> mouseState;
};