#include "gameGlobalInfo.h"

#include <sp2/scene/node.h>
#include <sp2/assert.h>


sp::P<GameGlobalInfo> GameGlobalInfo::instance;

GameGlobalInfo::GameGlobalInfo()
: sp::Scene("GAME_GLOBAL_INFO")
{
    getRoot()->multiplayer.enable();

    instance = this;
}

sp::P<GameGlobalInfo> GameGlobalInfo::getInstance()
{
    return instance;
}
