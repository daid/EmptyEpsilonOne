#include "craft.h"

#include <sp2/graphics/meshdata.h>
#include <sp2/graphics/textureManager.h>
#include <sp2/multiplayer/registry.h>
#include <sp2/collision/2d/circle.h>

REGISTER_MULTIPLAYER_CLASS(Craft);

Craft::Craft(sp::P<sp::Node> parent)
: SpaceObject(parent)
{
    radar_blip.type = sp::RenderData::Type::Normal;
    radar_blip.mesh = sp::MeshData::createQuad(sp::Vector2f(30, 30));
    radar_blip.texture = sp::texture_manager.get("gui/radar/arrow.png");

    impulse.request = 1.0;

    sp::collision::Circle2D shape(50.0);
    shape.type = sp::collision::Shape::Type::Dynamic;
    setCollisionShape(shape);
}

void Craft::onUpdate(float delta)
{
    if (impulse.current < impulse.request)
        impulse.current = std::min(impulse.request, impulse.current + delta * (impulse.config.acceleration / impulse.config.top_speed));
    else if (impulse.current > impulse.request)
        impulse.current = std::max(impulse.request, impulse.current - delta * (impulse.config.acceleration / impulse.config.top_speed));

    setLinearVelocity(sp::Vector2d(0.0, 1.0).rotate(getRotation2D()) * impulse.current * impulse.config.top_speed);
    setRotation(getRotation2D() + delta * 10.0);
}
