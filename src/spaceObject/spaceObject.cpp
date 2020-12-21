#include "spaceObject.h"

SpaceObject::SpaceObject(sp::P<sp::Node> parent)
    : sp::Node(parent)
{
    multiplayer.enable();
    multiplayer.enableDeadReckoning({});

    radar_blip.shader = sp::Shader::get("shader/radar/blip.shader");
}

void SpaceObject::renderOnRadar(sp::RenderQueue &queue)
{
    if (radar_blip.type != sp::RenderData::Type::None)
        queue.add(getGlobalTransform(), radar_blip);
}

void SpaceObject::onRegisterScriptBindings(sp::script::BindingClass &script_binding_class)
{
    script_binding_class.bind("setPosition", static_cast<void (sp::Node::*)(sp::Vector2d)>(&sp::Node::setPosition));
    script_binding_class.bind("setRotation", static_cast<void (sp::Node::*)(double)>(&sp::Node::setRotation));
    script_binding_class.bindProperty("position", &sp::Node::getPosition2D, &sp::Node::setPosition);
    script_binding_class.bindProperty("rotation", &sp::Node::getRotation2D, &sp::Node::setRotation);
}
