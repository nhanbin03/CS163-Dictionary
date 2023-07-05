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
            mInputText.push_back(key);
            key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE) && mInputText.size() > 0) {
            mInputText.pop_back();
        }
    }
}

void InputBox::draw() {
    DrawRectangleRounded(mRect, mCornerRoundness, ROUNDED_SEGMENTS, mColor);
    if (mBorderThickness != 0)
        DrawRectangleRoundedLines(mRect, mCornerRoundness, ROUNDED_SEGMENTS,
                                  mBorderThickness, mBorderColor);

    int textSize = mRect.height * 2 / 3;
    std::string displayText = mInputText;
    if (mIsFocused)
        displayText += '_';
    Vector2 textBounds =
        MeasureTextEx(FontHolder::getInstance().get(FontID::Inter, textSize),
                      displayText.c_str(), textSize, 0);

    BeginScissorMode(mRect.x, mRect.y, mRect.width, mRect.height);
    DrawTextEx(
        FontHolder::getInstance().get(FontID::Inter, textSize),
        displayText.c_str(),
        {mRect.x + textSize / 3, mRect.y + mRect.height / 2 - textBounds.y / 2},
        textSize, 0, mTextColor);
    EndScissorMode();
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
