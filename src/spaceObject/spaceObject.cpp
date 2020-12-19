#include "spaceObject.h"

SpaceObject::SpaceObject(sp::P<sp::Node> parent)
: sp::Node(parent)
{
    multiplayer.enable();
    multiplayer.enableDeadReckoning({});

    radar_blip.shader = sp::Shader::get("shader/radar/blip.shader");
}

void SpaceObject::renderOnRadar(sp::RenderQueue& queue)
{
    if (radar_blip.type != sp::RenderData::Type::None)
        queue.add(getGlobalTransform(), radar_blip);
}
