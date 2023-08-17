#include "WordInfo.h"

WordInfo::WordInfo(Core& dict)
: mDict(dict) {
    mReturnButton.setRect({341, 532, 75, 75});
    mReturnButton.setBorderThickness(0);
    mReturnButton.setColor(BLANK);
    mReturnButton.setTexture(
        TextureHolder::getInstance().get(TextureID::Return));
    mReturnButton.setCallback([this]() {
        this->mWord = nullptr;
    });
}

WordInfo::~WordInfo() {
}

void WordInfo::update(float dt) {
    if (mWord == nullptr)
        return;

    mPositionY += (GetMouseWheelMove() * 20);

    if (mPositionY < 0) {
        mPositionY = 0;
    }

    mReturnButton.update(dt);
}

void WordInfo::draw() {
    if (mWord == nullptr)
        return;

    DrawRectangleRec(mRect, AppColor::BACKGROUND_1);

    TextBox wordText(mWord->orgStr, {mRect.x + 13, mRect.y + 2, 508, 72});
    wordText.setTextSize(62);
    wordText.setBorderColor(BLANK);
    wordText.setColor(BLANK);
    wordText.makeShort();
    wordText.draw();

    drawDefinitions();

    mReturnButton.draw();
}

void WordInfo::setRect(Rectangle rect) {
    mRect = rect;
}

void WordInfo::setWord(Core::Word* word) {
    mWord = word;
    mPositionY = 0;
}

bool WordInfo::isActivated() {
    return mWord != nullptr;
}

void WordInfo::drawDefinitions() {
    BeginScissorMode(358, 279, 616, 361);
    int startingPosY = 279 + mPositionY;
    int cnt = 0;
    for (auto defPtr : mWord->defs) {
        if (defPtr->isDeleted()) continue;
        cnt++;
        TextBox wordText(std::to_string(cnt) + ". " + defPtr->orgStr, {358, startingPosY,
                                            616, 1});
        wordText.setBorderColor(BLANK);
        wordText.setColor(BLANK);
        wordText.setTextSize(22);
        wordText.draw();

        startingPosY += wordText.getHeight();
    }
    EndScissorMode();
}
