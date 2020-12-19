#pragma once

#include "spaceObject.h"

class Asteroid : public SpaceObject
{
public:
    Asteroid(sp::P<sp::Node> parent);
};