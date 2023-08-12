#ifndef WORDLIST_H
#define WORDLIST_H

#include "Core/Core.h"
#include "GUIComponents/Button.h"
#include "GUIComponents/TextBox.h"

#include "raylib.h"

class WordList {
public:
    WordList(const std::vector<Core::Word *> &list);
    ~WordList();

    void update(float dt);
    void draw();

    void setRect(Rectangle rect);

    void resetPosition();

private:
    const std::vector<Core::Word*> &mList;

    Rectangle mRect;
    float mRowHeight;

    bool mIsHistory{false};

    int mPositionY{0};
};

#endif // WORDLIST_H
