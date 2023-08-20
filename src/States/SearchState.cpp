#include "SearchState.h"

#include "raylib.h"

#include <cassert>
#include <iostream>

SearchState::SearchState(StateStack &stack, Context context)
: State(stack, context)
, mScrollList(mWordList) {
    mNavBar.setCurNav(NavBar::NavID::Search);

    // Search bar
    mSearchBar.setRect({334, 99, 456, 40});
    mSearchBar.setPlaceHolder("Type Something...");
    mSearchBar.setTextSize(24);
    mSearchBar.setBorderColor(BLANK);

    // Search button
    mSearchButton.setRect({859, 99, 123, 40});
    mSearchButton.setText("Search");
    mSearchButton.setTextSize(24);
    mSearchButton.setContentColor(AppColor::TEXT_CONTRAST);
    mSearchButton.setColor(AppColor::PRIMARY);
    mSearchButton.setCornerRoundness(0.6);
    mSearchButton.setCallback([this]() {
        if (this->mIsDefinitionSearch) {
            this->mWordList =
                Dictionary::getInstance().getDict().searchDefinition(
                    this->mSearchBar.getInputText());
        } else {
            this->mWordList = Dictionary::getInstance().getDict().searchKeyword(
                this->mSearchBar.getInputText());
        }
        if (this->mWordList.size() > Core::RESULT_LIMIT)
            this->mWordList.resize(Core::RESULT_LIMIT);
        this->mScrollList.resetPosition();
    });

    // Scroll list
    mScrollList.setRect({341, 163, 641, 477});

    // Mode button
    mModeButton.setRect({688, 20, 309, 47});
    mModeButton.setTexture(
        TextureHolder::getInstance().get(TextureID::DefinitionSwitch));
    mModeButton.setColor(BLANK);
    mIsDefinitionSearch = false;
    mModeButton.setCallback([this]() {
        if (this->mIsDefinitionSearch) {
            this->mModeButton.setTexture(
                TextureHolder::getInstance().get(TextureID::DefinitionSwitch));
            this->mIsDefinitionSearch = false;
        } else {
            this->mModeButton.setTexture(
                TextureHolder::getInstance().get(TextureID::KeywordSwitch));
            this->mIsDefinitionSearch = true;
        }
    });

    mWordList = Dictionary::getInstance().getDict().searchKeyword("a b");
}

SearchState::~SearchState() {
}

bool SearchState::update(float dt) {
    mScrollList.update(dt);
    mSearchBar.update(dt);
    mSearchButton.update(dt);
    mModeButton.update(dt);
    mNavBar.update(dt);
    return true;
}

void SearchState::draw() {
    ClearBackground(AppColor::BACKGROUND_1);
    mScrollList.draw();
    mSearchBar.draw();
    mSearchButton.draw();
    mModeButton.draw();
    mNavBar.draw();
    DrawLineEx({341, 163}, {982, 163}, 1, AppColor::TEXT);
}
