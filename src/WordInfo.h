#ifndef WORDINFO_H
#define WORDINFO_H

#include "Core/Core.h"
#include "GUIComponents/Button.h"
#include "GUIComponents/TextBox.h"
#include "GUIComponents/InputBox.h"

#include "raylib.h"

class WordInfo {
public:
    WordInfo();
    ~WordInfo();

    void update(float dt);
    void draw();

    void setRect(Rectangle rect);

    void setWord(Core::Word* word);

    bool isActivated();

private:
    Core::Word* mWord{nullptr};

    Rectangle mRect;

    Button mReturnButton;

    int mPositionY{0};

    bool mEditMode{false};
    std::vector<InputBox::Ptr> mDefEdittors;
    Button mAddDefBtn;

private:
    void drawDefinitions();

};


#endif // WORDINFO_H
