#include "WordInfo.h"

WordInfo::WordInfo() {
    mReturnButton.setRect({341, 532, 75, 75});
    mReturnButton.setBorderThickness(0);
    mReturnButton.setColor(BLANK);
    mReturnButton.setTexture(
        TextureHolder::getInstance().get(TextureID::Return));
    mReturnButton.setCallback([this]() {
        this->mWord = nullptr;
    });
    mEditMode = true;
}

WordInfo::~WordInfo() {
}

void WordInfo::update(float dt) {
    if (mWord == nullptr)
        return;

    mPositionY += (GetMouseWheelMove() * 20);

    if (mPositionY > 0) {
        mPositionY = 0;
    }

    // Update def edittors
    while (mDefEdittors.size() > mWord->defs.size()) mDefEdittors.pop_back();
    float startingPosY = 282 + mPositionY;
    for (int i = 0; i < mWord->defs.size(); i++) {
        if (i >= mDefEdittors.size()) {
            mDefEdittors.push_back(std::make_unique<InputBox>(mWord->defs[i]->orgStr));
            mDefEdittors.back()->setColor(AppColor::BACKGROUND_1);
            mDefEdittors.back()->setWrapped();
            mDefEdittors.back()->setTextSize(22);
            mDefEdittors.back()->setBorderThickness(1);
            mDefEdittors.back()->setCornerRoundness(0.54);
        }
        if (mWord->defs[i]->isDeleted())
            continue;

        mDefEdittors[i]->setRect({343, startingPosY, 585, 0});

        if (mEditMode) {
            if (startingPosY < 282) {
                mDefEdittors[i]->deactivateClickability();
            } else {
                mDefEdittors[i]->activateClickability();
            }
            mDefEdittors[i]->update(dt);
        }
        startingPosY += mDefEdittors[i]->getHeight() + 20;
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
    BeginScissorMode(341, 279, 616, 361);
    
    if (mEditMode) {
        for (auto inputPtr : mDefEdittors) {
            inputPtr->draw();
        }
    } else {
        int startingPosY = 279 + mPositionY;
        int cnt = 0;
        for (auto defPtr : mWord->defs) {
            if (defPtr->isDeleted())
                continue;
            cnt++;
            TextBox wordText(std::to_string(cnt) + ". " + defPtr->orgStr,
                             {358, startingPosY, 616, 1});
            wordText.setBorderColor(BLANK);
            wordText.setColor(BLANK);
            wordText.setTextSize(22);
            wordText.draw();

            startingPosY += wordText.getHeight();
        }
    }
    EndScissorMode();
}
