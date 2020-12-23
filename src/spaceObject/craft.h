#pragma once

#include "spaceObject.h"

class Craft : public SpaceObject
{
public:
    Craft(sp::P<sp::Node> parent);

    virtual void onUpdate(float delta) override;

    struct {
        double target = 0.0;
        double request = 0.0;
        struct {
            double speed = 10.0;
        } config;
    } maneuvering;
    struct {
        double request = 0.0;
        double current = 0.0;

        struct {
            double top_speed = 100.0; 
            double acceleration = 100.0;
        } config;
    } impulse;
    struct {
        int request = 0;
        double current = 0.0;
        struct {
            int max_level = 4;
            double speed_per_level = 1000.0;
            double charge_time = 4.0; // time it takes to charge 1 warp level up.
            double discharge_time = 2.0; // time it takes to discharge 1 warp level down.
        } config;
    } warpdrive;
    struct
    {
        double short_range = 5000;
        double long_range = 25000;
    } sensors;

    const sp::string& getCallsign() { return callsign; }
    void setCallsign(const sp::string& callsign);
private:
    sp::string callsign;
};
