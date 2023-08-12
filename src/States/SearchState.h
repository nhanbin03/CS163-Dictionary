#ifndef STATES_SEARCHSTATE_H
#define STATES_SEARCHSTATE_H

#include "../Core/Dictionary.h"
#include "../GUIComponents/TextBox.h"
#include "../GUIComponents/InputBox.h"
#include "../GUIComponents/Button.h"
#include "State.h"

#include <map>

class SearchState : public State {
public:
    SearchState(StateStack& stack, Context context);
    ~SearchState();

    bool update(float dt);
    void draw();

private:
    Core& mDict;

private: // UI elements
    InputBox mSearchBar;
    Button mSearchButton;
};

#endif // STATES_SEARCHSTATE_H
