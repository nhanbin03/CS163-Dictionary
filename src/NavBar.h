#ifndef NAVBAR_H
#define NAVBAR_H

#include "GUIComponents/Button.h"
#include "GUIComponents/GUIComponent.h"

#include "raylib.h"

#include <functional>
#include <map>
#include <string>

class NavBar : public GUIComponent {
public:
    enum class NavID {
        None,
        Search,
        Favorite,
        Game
    };

public:
    NavBar();

    void update(float dt);
    void draw();

    void addNav(NavID id, std::function<void()> navigate);
    void setCurNav(NavID id);

private:
    Button mDatasetSwitch;
    std::map<NavID, Button> mNavButtons;
    NavID mSelection{NavID::None};
};

#endif // NAVBAR_H
