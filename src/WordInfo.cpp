#include "WordInfo.h"

WordInfo::WordInfo(Core& dict)
: mDict(dict) {
}

WordInfo::~WordInfo() {
}

void WordInfo::update(float dt) {
}

void WordInfo::draw() {
    if (mWord == nullptr) return;

    DrawRectangleRec(mRect, AppColor::BACKGROUND_1);

    TextBox wordText(mWord->orgStr, {mRect.x + 55, mRect.y + 2, 508, 72});
    wordText.setTextSize(62);
    wordText.setBorderColor(BLANK);
    wordText.setColor(BLANK);
    wordText.makeShort();
    wordText.draw();
}

void WordInfo::setRect(Rectangle rect) {
    mRect = rect;
}

void WordInfo::setWord(Core::Word* word) {
    mWord = word;
}
