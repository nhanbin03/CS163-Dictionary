#include "SearchState.h"

#include "raylib.h"

#include <cassert>
#include <iostream>

SearchState::SearchState(StateStack &stack, Context context)
: State(stack, context)
, mDict(Dictionary::CORE[0])
 {
    // Search bar
    mSearchBar.setRect({334, 99, 499, 40});
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
}

SearchState::~SearchState() {
}

bool SearchState::update(float dt) {

    DrawLineEx({341, 163}, {982, 163}, 1, AppColor::TEXT);
    mSearchBar.update(dt);
    mSearchButton.update(dt);
    return true;
}

void SearchState::draw() {
    ClearBackground(AppColor::BACKGROUND_1);
    mSearchBar.draw();
    mSearchButton.draw();
}
