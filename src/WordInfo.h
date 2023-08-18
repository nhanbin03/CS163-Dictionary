#ifndef WORDINFO_H
#define WORDINFO_H

#include "Core/Core.h"
#include "GUIComponents/Button.h"
#include "GUIComponents/TextBox.h"

#include "raylib.h"

class WordInfo
{
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

private:
    void drawDefinitions();

};


#endif // WORDINFO_H
