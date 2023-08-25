#include "Application.h"
#include "ResourceHolders/ResourceIdentifiers.h"
#include "States/SearchState.h"
#include "States/FavoriteState.h"
#include "States/GameState.h"
#include "States/WordGameState.h"
#include "States/DefinitionGameState.h"
#include "States/SettingsState.h"
#include "States/StateIdentifiers.h"

#include "raylib.h"

#include <iostream>

Application::Application()
: mStateStack(State::Context()) {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetConfigFlags(FLAG_WINDOW_ALWAYS_RUN);

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(FPS);

    loadTextures();
    loadFonts();

    // SetWindowIcon(LoadImageFromTexture(
    //     TextureHolder::getInstance().get(TextureID::IconLogo)));

    registerStates();
    mStateStack.pushState(StateIDs::Search);
}

Application::~Application() {
    CloseWindow();
}

void Application::run() {
    while (!WindowShouldClose()) {
        update(GetFrameTime());
        render();
    }
}

void Application::update(float dt) {
    mStateStack.update(dt);
}

void Application::render() {
    BeginDrawing();
    mStateStack.draw();
    EndDrawing();
}

void Application::registerStates() {
    mStateStack.registerState<SearchState>(StateIDs::Search);
    mStateStack.registerState<FavoriteState>(StateIDs::Favorite);
    mStateStack.registerState<GameState>(StateIDs::Game);
    mStateStack.registerState<WordGameState>(StateIDs::WordGame);
    mStateStack.registerState<DefinitionGameState>(StateIDs::DefinitionGame);
    mStateStack.registerState<SettingsState>(StateIDs::Settings);
}

void Application::loadTextures() {
    std::string BASE_PATH = "asset/texture/";
    TextureHolder::getInstance().load(TextureID::DefinitionSwitch,
                                      BASE_PATH + "DefinitionSwitch.png");
    TextureHolder::getInstance().load(TextureID::KeywordSwitch,
                                      BASE_PATH + "KeywordSwitch.png");
    TextureHolder::getInstance().load(TextureID::Return,
                                      BASE_PATH + "Return.png");
    TextureHolder::getInstance().load(TextureID::DatasetSwitch,
                                      BASE_PATH + "DatasetSwitch.png");
    TextureHolder::getInstance().load(TextureID::SearchNav,
                                      BASE_PATH + "SearchNav.png");
    TextureHolder::getInstance().load(TextureID::FavoriteNav,
                                      BASE_PATH + "FavoriteNav.png");
    TextureHolder::getInstance().load(TextureID::GameNav,
                                      BASE_PATH + "GameNav.png");
    TextureHolder::getInstance().load(TextureID::OptionPanel,
                                      BASE_PATH + "OptionPanel.png");
    TextureHolder::getInstance().load(TextureID::Edit, BASE_PATH + "Edit.png");
    TextureHolder::getInstance().load(TextureID::Cancel,
                                      BASE_PATH + "Cancel.png");
    TextureHolder::getInstance().load(TextureID::Save, BASE_PATH + "Save.png");
    TextureHolder::getInstance().load(TextureID::AddDefinition,
                                      BASE_PATH + "AddDefinition.png");
    TextureHolder::getInstance().load(TextureID::StarUnselected,
                                      BASE_PATH + "StarUnselected.png");
    TextureHolder::getInstance().load(TextureID::StarSelected,
                                      BASE_PATH + "StarSelected.png");
    TextureHolder::getInstance().load(TextureID::Settings,
                                      BASE_PATH + "Settings.png");
    TextureHolder::getInstance().load(TextureID::Delete,
                                      BASE_PATH + "Delete.png");
    TextureHolder::getInstance().load(TextureID::Details,
                                      BASE_PATH + "Details.png");
    TextureHolder::getInstance().load(TextureID::WordGame,
                                      BASE_PATH + "WordGame.png");
    TextureHolder::getInstance().load(TextureID::DefinitionGame,
                                      BASE_PATH + "DefinitionGame.png");
    TextureHolder::getInstance().load(TextureID::Remove,
                                      BASE_PATH + "Remove.png");
}

void Application::loadFonts() {
    std::string BASE_PATH = "asset/font/";
    FontHolder::getInstance().load(FontID::Inter, BASE_PATH + "Inter.ttf");
    FontHolder::getInstance().load(FontID::Inter_Bold,
                                   BASE_PATH + "Inter_Bold.ttf");
}
