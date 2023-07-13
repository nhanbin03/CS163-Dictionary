#include "InputBox.h"

#include <iostream>

InputBox::InputBox(Rectangle bounds) {
    mRect = bounds;
    mColor = WHITE;
    mBorderColor = BLACK;
    mBorderThickness = 1;
}

InputBox::~InputBox() {
}

void InputBox::reset() {
    mInputText = "";
}

void InputBox::update(float dt) {
    checkInteraction();

    if (mIsFocused) {
        int key = GetCharPressed();
        while (key > 0) {
            mInputText.insert(mInputText.begin() + mIndexPos, key);
            mIndexPos++;
            key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE) && mIndexPos > 0) {
            mInputText.erase(mInputText.begin() + mIndexPos - 1);
            mIndexPos--;
        }
        if (IsKeyPressed(KEY_RIGHT) && mIndexPos < mInputText.size()) {
            mIndexPos++;
        }
        if (IsKeyPressed(KEY_LEFT) && mIndexPos > 0) {
            mIndexPos--;
        }
    }

    mCursorTick += dt;
    if (mCursorTick > 2 * CURSOR_TICK_COUNT) {
        mCursorTick -= 2 * CURSOR_TICK_COUNT;
    }
}

void InputBox::draw() {
    DrawRectangleRounded(mRect, mCornerRoundness, ROUNDED_SEGMENTS, mColor);
    if (mBorderThickness != 0)
        DrawRectangleRoundedLines(mRect, mCornerRoundness, ROUNDED_SEGMENTS,
                                  mBorderThickness, mBorderColor);
    if (mIsWrapped) {
        drawTextWrapped();
    } else {
        drawTextOverflow();
    }
}

void InputBox::setCornerRoundness(float cornerRoundness) {
    mCornerRoundness = cornerRoundness;
}

std::string InputBox::getInputText() const {
    return mInputText;
}

std::function<bool(std::string)> InputBox::integerValidator(int min, int max) {
    return [min, max](std::string str) -> bool {
        if (!std::regex_match(str, std::regex("[0-9]+"))) {
            return false;
        }
        int num = std::stoi(str);
        return (min <= num && num <= max);
    };
}

std::function<bool(std::string)>
InputBox::integerSpaceSeparatedListValidator() {
    return [](std::string str) -> bool {
        return std::regex_match(str,
                                std::regex("(?:-?\\d+)?(?:\\s+-?\\d+)*\\s*"));
    };
}

void InputBox::checkInteraction() {
    Vector2 mousePoint = GetMousePosition();

    if (CheckCollisionPointRec(mousePoint, mRect)) {
        SetMouseCursor(MOUSE_CURSOR_IBEAM);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            mIsFocused = true;
        }
    } else {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            mIsFocused = false;
        }
    }
}

void InputBox::drawTextOverflow() {
    int textSize = mTextSize;
    if (mTextSize == 0) {
        textSize = mRect.height * 2 / 3;
    }
    std::string displayText = mInputText;
    Vector2 textBounds =
        MeasureTextEx(FontHolder::getInstance().get(FontID::Inter, textSize),
                      displayText.c_str(), textSize, 0);

    BeginScissorMode(mRect.x + textSize / 3, mRect.y,
                     mRect.width - textSize / 3, mRect.height);
    float startingX = mRect.x + textSize / 3;
    float startingY = mRect.y + textSize / 3;
    DrawTextEx(FontHolder::getInstance().get(FontID::Inter, textSize),
               displayText.c_str(), {startingX, startingY}, textSize, 0,
               mTextColor);
    if (mIsFocused)
        drawCursorIndicator(
            startingX
                + MeasureTextEx(
                      FontHolder::getInstance().get(FontID::Inter, textSize),
                      displayText.substr(0, mIndexPos).c_str(), textSize, 0)
                      .x,
            startingY, startingY + textBounds.y);
    EndScissorMode();
}

void InputBox::drawTextWrapped() {
}

void InputBox::drawCursorIndicator(float x, float y1, float y2) {
    if (mCursorTick < CURSOR_TICK_COUNT) {
        DrawLineEx({x, y1}, {x, y2}, abs(y1 - y2) * 0.05, mTextColor);
    }
}
