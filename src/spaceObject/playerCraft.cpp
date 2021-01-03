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
    multiplayer.replicate(&PlayerCraft::serverSetWarpRequest);
    multiplayer.replicate(&PlayerCraft::serverJumpRequest);
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

void PlayerCraft::commandSetWarpRequest(int level)
{
    level = std::clamp(level, 0, warpdrive.config.max_level);
    warpdrive.request = level;
    multiplayer.callOnServer(&PlayerCraft::serverSetWarpRequest, level);
}

void PlayerCraft::commandJumpRequest(double distance)
{
    multiplayer.callOnServer(&PlayerCraft::serverJumpRequest, distance);
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

void PlayerCraft::serverSetWarpRequest(int level)
{
    level = std::clamp(level, 0, warpdrive.config.max_level);
    warpdrive.request = level;
}

void PlayerCraft::serverJumpRequest(double distance)
{
    requestJump(distance);
}