#ifndef GUICOMPONENTS_INPUTBOX_H
#define GUICOMPONENTS_INPUTBOX_H

#include "Button.h"
#include "GUIComponent.h"

#include "raylib.h"

#include <functional>
#include <memory>
#include <regex>
#include <string>

class InputBox : public GUIComponent {
public:
    static constexpr float CURSOR_TICK_COUNT = 0.5;

public:
    typedef std::shared_ptr<InputBox> Ptr;

public:
    explicit InputBox(Rectangle bounds = {0, 0, 0, 0});
    ~InputBox();

    void reset();

    void update(float dt);
    void draw();

    void setCornerRoundness(float cornerRoundness);

    std::string getInputText() const;

public:
    static std::function<bool(std::string)> integerValidator(int min, int max);
    static std::function<bool(std::string)>
    integerSpaceSeparatedListValidator();

private:
    void checkInteraction();

    void drawTextOverflow();
    void drawTextWrapped();

    void drawCursorIndicator(float x, float y1, float y2);

private:
    std::string mInputText;
    Color mTextColor{BLACK};
    int mTextSize{0};

    bool mIsFocused{false};
    int mIndexPos{0};
    float mCursorTick{0};

    float mCornerRoundness{0.5};

    bool mIsWrapped{false};
};

#endif // GUICOMPONENTS_INPUTBOX_H
