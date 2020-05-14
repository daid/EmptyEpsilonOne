#pragma once

#include <sp2/scene/scene.h>


class GameGlobalInfo : public sp::Scene
{
public:
    GameGlobalInfo();

    static sp::P<GameGlobalInfo> getInstance();
private:
    static sp::P<GameGlobalInfo> instance;
};
