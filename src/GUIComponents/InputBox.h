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

private:
    std::string mInputText;
    Color mTextColor{BLACK};

    bool mIsFocused{false};

    float mCornerRoundness{0.5};
};

#endif // GUICOMPONENTS_INPUTBOX_H
