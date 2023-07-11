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
    enum KeyState { NONE = 0, HELD = 1, PRESSED = 2, RELEASED = 3 };

public: // Public methods
    Window(const Vect<uint32_t>& size, const std::string& title, const bool vsync, const bool outputFPS = false);
    void createSDLWindow(const std::string& title, const bool vsync);
    void destroy();

    static void setAllowedKeys(const std::vector<SDL_Keycode>& keys);

    // Call these once every frame
    static void updateMouse();
    static void updateKeyStates(); // Call this before Window::handleInputs(...)
    static void handleInputs(std::vector<Window*>& windows);
    static void handleInputs(std::vector<Window>& window);
    static void handleInputs(Window& window); // For single-window applications

    // Call once per frame per window
    void presentFrame(); // Displays changes to screen
    
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

    inline const uint32_t getID() const { return SDL_GetWindowID(window); };
    inline const bool isKeyFocused() const { return this == keyFocusedWindow; }
    inline const bool isMouseFocused() const { return this == mouseFocusedWindow; }

    // Adds key/mouse button if they don't exist
    static const bool keyHeld(const SDL_Keycode& key); // If the key is held
    static const bool keyPressed(const SDL_Keycode& key); // The frame on which the key was pressed
    static const bool keyReleased(const SDL_Keycode& key); // The frame on which the key was released

    static const bool mouseHeld(const uint8_t& button);
    static const bool mousePressed(const uint8_t& button);
    static const bool mouseReleased(const uint8_t& button);

    static inline const Vect<int32_t>& getMousePos() { return mousePos; }

private: // Private methods
    static void handleKey(const SDL_Keycode& key, const uint32_t type);
    static void handleWindowEvent(const SDL_Event& event, std::vector<Window*>& windows);
    static Window* find(const uint32_t id, std::vector<Window*>& windows); // Finds window with the given ID

private: // Variables
    // Key inputs
    static std::unordered_map<SDL_Keycode, Window::KeyState> keys; // key states
    static std::vector<SDL_Keycode> allowedKeys; // keys that are tracked
    const static std::vector<uint8_t> defaultClearColor; // clear color/default draw color

    // Mouse
    static Vect<int32_t> mousePos;
    static std::unordered_map<uint8_t, Window::KeyState> mouseState;

    // Focused windows
    static Window* keyFocusedWindow; // Window selected/in primary focus
    static Window* mouseFocusedWindow; // Mouse hovering over window

    SDL_Window* window;
    SDL_Renderer* renderer;

    bool closed;
    bool destroyed;
    const Vect<uint32_t> size;

    float deltaTime;
    uint64_t lastFrame;
    const bool outputFPS;
    uint64_t FPSCounter;
};