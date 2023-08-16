#ifndef WORDLIST_H
#define WORDLIST_H

#include "Core/Core.h"
#include "GUIComponents/Button.h"
#include "GUIComponents/TextBox.h"
#include "WordInfo.h"

#include "raylib.h"

class WordList {
public:
    WordList(const std::vector<Core::Word *> &list, Core& dict);
    ~WordList();

    void update(float dt);
    void draw();

    void setRect(Rectangle rect);

    void resetPosition();

private:
    void createNewButton();

private:
    const std::vector<Core::Word*> &mList;
    std::vector<Button::Ptr> mButtonList;

    Rectangle mRect;
    float mRowHeight;

    bool mIsHistory{false};

    int mPositionY{0};

    WordInfo mInfoPage;
};

#endif // WORDLIST_H
