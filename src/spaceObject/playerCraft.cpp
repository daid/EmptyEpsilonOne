#include "playerCraft.h"

#include <sp2/multiplayer/registry.h>

sp::PList<PlayerCraft> PlayerCraft::all;

REGISTER_MULTIPLAYER_CLASS(PlayerCraft);

PlayerCraft::PlayerCraft(sp::P<sp::Node> parent)
: Craft(parent)
{
    all.add(this);

    multiplayer.replicate(&PlayerCraft::serverSetManeuverTarget);
    multiplayer.replicate(&PlayerCraft::serverSetImpulseRequest);
}

void PlayerCraft::commandSetManeuverTarget(double target)
{
    maneuvering.target = target;
    maneuvering.request = 0.0;
    multiplayer.callOnServer(&PlayerCraft::serverSetManeuverTarget, target);
}

void PlayerCraft::commandSetImpulseRequest(double amount)
{
    amount = std::clamp(amount, -1.0, 1.0);
    impulse.request = amount;
    multiplayer.callOnServer(&PlayerCraft::serverSetImpulseRequest, amount);
}

void PlayerCraft::serverSetManeuverTarget(double target)
{
    maneuvering.target = target;
    maneuvering.request = 0.0;
}

void PlayerCraft::serverSetImpulseRequest(double amount)
{
    amount = std::clamp(amount, -1.0, 1.0);
    impulse.request = amount;
}