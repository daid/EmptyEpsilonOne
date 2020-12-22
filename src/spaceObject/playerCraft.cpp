#include "playerCraft.h"

#include <sp2/multiplayer/registry.h>

sp::PList<PlayerCraft> PlayerCraft::all;

REGISTER_MULTIPLAYER_CLASS(PlayerCraft);

PlayerCraft::PlayerCraft(sp::P<sp::Node> parent)
    : Craft(parent)
{
    all.add(this);
}