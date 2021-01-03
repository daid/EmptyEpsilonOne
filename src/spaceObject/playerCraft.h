#pragma once

#include "craft.h"

class PlayerCraft : public Craft
{
public:
    PlayerCraft(sp::P<sp::Node> parent);

    void commandSetManeuverTarget(double target);
    void commandSetImpulseRequest(double amount);
    void commandSetWarpRequest(int level);
    void commandJumpRequest(double distance);

    static sp::PList<PlayerCraft> all;

private:
    void serverSetManeuverTarget(double target);
    void serverSetImpulseRequest(double amount);
    void serverSetWarpRequest(int level);
    void serverJumpRequest(double distance);
};
