#pragma once

#include "craft.h"

class PlayerCraft : public Craft
{
public:
    PlayerCraft(sp::P<sp::Node> parent);

    static sp::PList<PlayerCraft> all;
};
