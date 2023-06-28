#ifndef STATES_HOMESTATE_H
#define STATES_HOMESTATE_H

#include "State.h"

#include <map>

class HomeState : public State {
public:
    HomeState(StateStack& stack, Context context);
    ~HomeState();

    bool update(float dt);
    void draw();
};

#endif // STATES_HOMESTATE_H
