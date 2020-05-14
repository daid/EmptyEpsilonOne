#include "spaceScene.h"

#include <sp2/scene/node.h>


SpaceScene::SpaceScene()
: sp::Scene("SPACE")
{
    getRoot()->multiplayer.enable();
}
