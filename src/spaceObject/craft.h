#pragma once

#include "spaceObject.h"

class Craft : public SpaceObject
{
public:
    Craft(sp::P<sp::Node> parent);

    virtual void onUpdate(float delta) override;

    struct {
        double request = 0.0;
        double current = 0.0;

        struct {
            double top_speed = 100.0; 
            double acceleration = 10.0;
        } config;
    } impulse;

    double rotation_speed = 10.0;
};
