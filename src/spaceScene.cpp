#include "spaceScene.h"

#include <sp2/scene/node.h>


SpaceScene::SpaceScene(const sp::string& name)
: sp::Scene(name)
{
    getRoot()->multiplayer.enable();
}
