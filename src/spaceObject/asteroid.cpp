#include "asteroid.h"

#include <sp2/graphics/meshdata.h>
#include <sp2/graphics/textureManager.h>
#include <sp2/multiplayer/registry.h>
#include <sp2/collision/2d/circle.h>


REGISTER_MULTIPLAYER_CLASS(Asteroid);

Asteroid::Asteroid(sp::P<sp::Node> parent)
: SpaceObject(parent)
{
    radar_blip.type = sp::RenderData::Type::Normal;
    radar_blip.color = sp::Color(1, 0.8, 0.4);
    radar_blip.mesh = sp::MeshData::createQuad(sp::Vector2f(10, 10));
    radar_blip.texture = sp::texture_manager.get("gui/radar/blip.png");

    sp::collision::Circle2D shape(120);
    shape.type = sp::collision::Shape::Type::Sensor;
    setCollisionShape(shape);
}
