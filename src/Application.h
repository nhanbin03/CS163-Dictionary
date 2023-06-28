#ifndef APPLICATION_H
#define APPLICATION_H

#include "ResourceHolders/FontHolder.h"
#include "ResourceHolders/TextureHolder.h"
#include "StateStack.h"

#include "raylib.h"

class Application {
public:
    static constexpr float WINDOW_WIDTH = 1440;
    static constexpr float WINDOW_HEIGHT = 950;
    static constexpr char *WINDOW_TITLE = "Dictionary";

    static constexpr int FPS = 60;

public:
    Application();
    ~Application();

    void run();

private:
    void update(float dt);
    void render();

    void registerStates();

    void loadTextures();
    void loadFonts();

private:
    StateStack mStateStack;
};

#endif // APPLICATION_H
