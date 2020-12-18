#pragma once

#include <sp2/graphics/scene/basicnoderenderpass.h>

class RadarRenderPass : public sp::BasicNodeRenderPass
{
public:
    void addNodeToRenderQueue(sp::RenderQueue& queue, sp::P<sp::Node>& node) override;
};