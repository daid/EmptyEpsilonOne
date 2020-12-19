#include "playerCraft.h"

#include <sp2/multiplayer/registry.h>

REGISTER_MULTIPLAYER_CLASS(PlayerCraft);

PlayerCraft::PlayerCraft(sp::P<sp::Node> parent)
: Craft(parent)
{
}