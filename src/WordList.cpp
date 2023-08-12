#include "WordList.h"

WordList::WordList(const std::vector<Core::Word*> &list)
: mList(list) {
    mRowHeight = 65;
}

WordList::~WordList() {
}

void WordList::update(float dt) {
    mPositionY += (GetMouseWheelMove() * 20);
}

void WordList::draw() {
    BeginScissorMode(mRect.x, mRect.y, mRect.width, mRect.height);
    for (int i = 0; i < mList.size(); i++) {
        int startingPosY = mRect.y + mPositionY + i * mRowHeight;
        TextBox wordText(mList[i]->orgStr, {mRect.x + 35, startingPosY + 7, mRect.width, mRowHeight});
        wordText.setBorderColor(BLANK);
        wordText.setTextSize(32);
        wordText.draw();
        DrawLineEx({mRect.x, startingPosY + mRowHeight}, {mRect.x + mRect.width, startingPosY + mRowHeight}, 0.5, AppColor::TEXT);
    }
    EndScissorMode();
}

void WordList::setRect(Rectangle rect) {
    mRect = rect;
}

void WordList::resetPosition() {
    mPositionY = 0;
}
