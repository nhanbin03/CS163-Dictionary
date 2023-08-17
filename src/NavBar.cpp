#include "NavBar.h"

#include <cassert>
#include <iostream>

NavBar::NavBar() {
    mRect = {0, 0, 299, 640};
    mColor = AppColor::BACKGROUND_2;

    mDatasetSwitch.setRect({26, 19, 246, 61});
    mDatasetSwitch.setBorderThickness(0);
    mDatasetSwitch.setColor(BLANK);
    mDatasetSwitch.setTexture(TextureHolder::getInstance().get(TextureID::DatasetSwitch));

}

void NavBar::update(float dt) {
    mDatasetSwitch.update(dt);
    for (auto& p : mNavButtons) {
        p.second.update(dt);
    }
}

void NavBar::draw() {
    DrawRectangleRec(mRect, mColor);
    mDatasetSwitch.draw();
    for (auto& p : mNavButtons) {
        p.second.draw();
        if (p.first == mSelection) {
            Rectangle rect = p.second.getRect();
            DrawRectangleRec(rect, GetColor(0x00000011));
            DrawLineEx({0, rect.y}, {0, rect.y + rect.height}, 8,
                       AppColor::PRIMARY); // Indicator
        }
    }
}

void NavBar::addNav(NavID id, std::function<void()> navigate) {
    Button navButton;
    const int BUTTON_HEIGHT = 56;
    navButton.setPosition(
        (Vector2){0, 112 + BUTTON_HEIGHT * mNavButtons.size()});
    navButton.setSize({getSize().x, BUTTON_HEIGHT});
    navButton.setCornerRoundness(0);

    TextureID buttonTextureID;
    switch (id) {
        case NavID::Search:
            buttonTextureID = TextureID::SearchNav;
            break;
        case NavID::Favorite:
            buttonTextureID = TextureID::FavoriteNav;
            break;
        case NavID::Game:
            buttonTextureID = TextureID::GameNav;
            break;
    }
    navButton.setTexture(TextureHolder::getInstance().get(buttonTextureID));

    navButton.setColor(AppColor::BACKGROUND_2);
    // navButton.setContentColor(AppColor::TEXT);
    navButton.setCallback(navigate);
    mNavButtons[id] = std::move(navButton);
}

void NavBar::setCurNav(NavID id) {
    auto found = mNavButtons.find(id);
    assert(found != mNavButtons.end());

    mSelection = id;
}
