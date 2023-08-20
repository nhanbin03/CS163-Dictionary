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

    mEditButton.setRect({916, 532, 75, 75});
    mEditButton.setBorderThickness(0);
    mEditButton.setColor(BLANK);
    mEditButton.setTexture(TextureHolder::getInstance().get(TextureID::Edit));
    mEditButton.setCallback([this]() {
        this->mEditMode = true;
        this->addEdittors();
    });

    mCancelButton.setRect({816, 532, 75, 75});
    mCancelButton.setBorderThickness(0);
    mCancelButton.setColor(BLANK);
    mCancelButton.setTexture(
        TextureHolder::getInstance().get(TextureID::Cancel));
    mCancelButton.setCallback([this]() {
        this->mEditMode = false;
    });

    mSaveButton.setRect({916, 532, 75, 75});
    mSaveButton.setBorderThickness(0);
    mSaveButton.setColor(BLANK);
    mSaveButton.setTexture(TextureHolder::getInstance().get(TextureID::Save));
    mSaveButton.setCallback([this]() {
        this->mEditMode = false;
        this->saveEdittors();
    });
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

    if (mEditMode) {
        updateEditMode(dt);
    } else {
        updateInfoMode(dt);
    }
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

    if (mEditMode) {
        mCancelButton.draw();
        mSaveButton.draw();
    } else {
        mReturnButton.draw();
        mEditButton.draw();
    }
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
    BeginScissorMode(341, 279, 641, 361);

    if (mEditMode) {
        drawEditMode();
    } else {
        drawInfoMode();
    }
    EndScissorMode();
}

void WordInfo::updateInfoMode(float dt) {
    mReturnButton.update(dt);
    mEditButton.update(dt);
}

void WordInfo::updateEditMode(float dt) {
    float startingPosY = 282 + mPositionY;
    for (int i = 0; i < mDefEdittors.size(); i++) {
        if (mWord->defs[i]->isDeleted())
            continue;

        mDefEdittors[i]->setRect({343, startingPosY, 637, 0});

        if (startingPosY < 282) {
            mDefEdittors[i]->deactivateClickability();
        } else {
            mDefEdittors[i]->activateClickability();
        }
        mDefEdittors[i]->update(dt);
        mDefEdittors[i]->setCornerRoundness(20 * 2 / mDefEdittors[i]->getHeight());
        startingPosY += mDefEdittors[i]->getHeight() + 20;
    }

    mCancelButton.update(dt);
    mSaveButton.update(dt);
}

void WordInfo::drawInfoMode() {
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

void WordInfo::drawEditMode() {
    for (auto inputPtr : mDefEdittors) {
        inputPtr->draw();
    }
}

void WordInfo::addEdittors() {
    mDefEdittors.clear();
    for (int i = 0; i < mWord->defs.size(); i++) {
        mDefEdittors.push_back(
            std::make_unique<InputBox>(mWord->defs[i]->orgStr));
        mDefEdittors.back()->setColor(AppColor::BACKGROUND_1);
        mDefEdittors.back()->setWrapped();
        mDefEdittors.back()->setTextSize(22);
        mDefEdittors.back()->setBorderThickness(1);
    }
}

void WordInfo::saveEdittors() {
    for (int i = 0; i < mDefEdittors.size(); i++) {
        if (i < mWord->defs.size()) {
            Dictionary::getInstance().getDict().editDefinition(mWord->defs[i], mDefEdittors[i]->getInputText());
        } else {
            Dictionary::getInstance().getDict().addDefinition(mDefEdittors[i]->getInputText(), mWord);
        }
    }
}

