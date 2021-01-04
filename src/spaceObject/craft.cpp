#include "craft.h"
#include "../multiplayer.h"

#include <sp2/graphics/meshdata.h>
#include <sp2/graphics/textureManager.h>
#include <sp2/multiplayer/registry.h>
#include <sp2/collision/2d/circle.h>

REGISTER_MULTIPLAYER_CLASS(Craft);

Craft::Craft(sp::P<sp::Node> parent)
: SpaceObject(parent)
{
    radar_blip.type = sp::RenderData::Type::Normal;
    radar_blip.mesh = sp::MeshData::createQuad(sp::Vector2f(10, 10));
    radar_blip.texture = sp::texture_manager.get("gui/radar/arrow.png");
    radar_blip.scale.x = 20.0;

    multiplayer.replicate(maneuvering.request, 0.1);
    multiplayer.replicate(maneuvering.target, 0.1);
    multiplayer.replicate(maneuvering.config.speed);

    multiplayer.replicate(impulse.request, 0.1);
    multiplayer.replicate(impulse.current, 0.1);
    multiplayer.replicate(impulse.config.top_speed);
    multiplayer.replicate(impulse.config.acceleration);

    multiplayer.replicate(warpdrive.request);
    multiplayer.replicate(warpdrive.current, 0.1);
    multiplayer.replicate(warpdrive.config.max_level);
    multiplayer.replicate(warpdrive.config.speed_per_level);
    multiplayer.replicate(warpdrive.config.charge_time);
    multiplayer.replicate(warpdrive.config.discharge_time);

    multiplayer.replicate(jumpdrive.charge, 0.1);
    multiplayer.replicate(jumpdrive.jump_delay, 0.5);
    multiplayer.replicate(jumpdrive.config.min_distance);
    multiplayer.replicate(jumpdrive.config.max_distance);
    multiplayer.replicate(jumpdrive.config.charge_time);
    multiplayer.replicate(jumpdrive.config.jump_delay);

    multiplayer.replicate(sensors.short_range);
    multiplayer.replicate(sensors.long_range);

    sp::collision::Circle2D shape(50.0);
    shape.type = sp::collision::Shape::Type::Dynamic;
    setCollisionShape(shape);
}

void Craft::onUpdate(float delta)
{
    if (jumpdrive.jump_delay > 0.0)
    {
        jumpdrive.jump_delay -= delta;
        if (jumpdrive.jump_delay <= 0.0)
        {
            if (isServer())
                executeJump(jumpdrive.jump_distance);
            jumpdrive.jump_delay = 0.0;
        }
        warpdrive.request = 0.0;
        impulse.request = 0.0;
    }
    else
    {
        jumpdrive.charge = std::min(jumpdrive.charge + jumpdrive.config.max_distance * delta / jumpdrive.config.charge_time, jumpdrive.config.max_distance);
    }

    if (warpdrive.request > 0 || warpdrive.current > 0.0)
    {
        if (impulse.current > 0.0)
            impulse.current = std::max(0.0, impulse.current - delta * (impulse.config.acceleration / impulse.config.top_speed));
        else if (impulse.current < 0.0)
            impulse.current = std::min(0.0, impulse.current + delta * (impulse.config.acceleration / impulse.config.top_speed));
        else if (warpdrive.current < warpdrive.request)
            warpdrive.current = std::min(double(warpdrive.request), warpdrive.current + delta / warpdrive.config.charge_time);
        else
            warpdrive.current = std::max(double(warpdrive.request), warpdrive.current - delta / warpdrive.config.discharge_time);
    }
    else
    {
        if (impulse.current < impulse.request)
            impulse.current = std::min(impulse.request, impulse.current + delta * (impulse.config.acceleration / impulse.config.top_speed));
        else if (impulse.current > impulse.request)
            impulse.current = std::max(impulse.request, impulse.current - delta * (impulse.config.acceleration / impulse.config.top_speed));
    }

    double impulse_speed = impulse.current * impulse.config.top_speed;
    double warp_speed = warpdrive.current * warpdrive.config.speed_per_level;
    setLinearVelocity(sp::Vector2d(1.0, 0.0).rotate(getRotation2D()) * (impulse_speed + warp_speed));

    if (std::abs(maneuvering.request) >= 0.005)
    {
        maneuvering.target = getRotation2D();
        setAngularVelocity(maneuvering.request * maneuvering.config.speed);
    } else {
        double rotation = getRotation2D();
        double diff = sp::angleDifference(rotation, maneuvering.target);
        diff = std::clamp(diff, -1.0, 1.0);
        setAngularVelocity(diff * maneuvering.config.speed);
    }
}

void Craft::setCallsign(const sp::string& callsign)
{
    this->callsign = callsign;
}

bool Craft::requestJump(double distance)
{
    if (jumpdrive.charge < jumpdrive.config.max_distance) // You can only jump when the drive is fully charged
        return false;
    if (jumpdrive.jump_delay > 0)
        return false;
    distance = std::min(distance, jumpdrive.charge);
    jumpdrive.jump_distance = distance;
    jumpdrive.jump_delay = jumpdrive.config.jump_delay;
    jumpdrive.charge -= distance;
    return true;
}

void Craft::executeJump(double distance)
{
    //TODO: Damage correction
    //TODO: Warp jammers
    //TODO: System heat
    auto target_position = getPosition2D() + sp::Vector2d(distance, 0).rotate(getRotation2D());

    setPosition(target_position);
}
