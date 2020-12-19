#pragma once

#include <sp2/scene/node.h>
#include <sp2/graphics/scene/renderqueue.h>

class SpaceObject : public sp::Node
{
public:
    SpaceObject(sp::P<sp::Node> parent);

    virtual void renderOnRadar(sp::RenderQueue& queue);

protected:
    sp::RenderData radar_blip;
};