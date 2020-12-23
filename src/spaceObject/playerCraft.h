#pragma once

#include "craft.h"

class PlayerCraft : public Craft
{
public:
    PlayerCraft(sp::P<sp::Node> parent);

    void commandSetManeuverTarget(double target);
    void commandSetImpulseRequest(double amount);

    static sp::PList<PlayerCraft> all;

private:
    void serverSetManeuverTarget(double target);
    void serverSetImpulseRequest(double amount);
};
