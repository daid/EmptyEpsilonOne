#pragma once

#include <sp2/graphics/scene/renderpass.h>

class RadarRenderPass : public sp::RenderPass
{
public:
    void render(sp::RenderQueue &queue) override;
};