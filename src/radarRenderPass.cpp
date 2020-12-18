#include "radarRenderPass.h"

#include <sp2/scene/camera.h>
#include <sp2/scene/scene.h>
#include <sp2/graphics/opengl.h>
#include "gui/radar.h"

void RadarRenderPass::addNodeToRenderQueue(sp::RenderQueue& queue, sp::P<sp::Node>& node)
{
    if (node->render_data.type == sp::RenderData::Type::Custom1)
    {
        sp::P<RadarWidget> radar_widget = node;
        
        
        //We need to set a new camera, which centers the radar view target position on
        //the center of the radar and has the correct scale.
        //TODO: Currently centers on the screen, while the widget could be at a different position
        queue.setCamera(node->getScene()->getCamera()->getProjectionMatrix(), sp::Matrix4x4f::identity());
        //Render the radar background, and set the stencil value to 1 for all these pixels.
        queue.add([](){
            glEnable(GL_STENCIL_TEST);    
            glStencilFunc(GL_ALWAYS, 1, 0xff);
            glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
        });
        sp::RenderData data;
        data = node->render_data;
        data.type = sp::RenderData::Type::Normal;
        data.color = sp::Color(0,0,0);
        queue.add(sp::Matrix4x4f::identity(), data);

        float scale = std::min(radar_widget->getRenderSize().x, radar_widget->getRenderSize().y) * 0.5;
        queue.setCamera(node->getScene()->getCamera()->getProjectionMatrix(), sp::Matrix4x4f::scale(scale,scale,1) * sp::Matrix4x4f::fromQuaternion(sp::Quaternionf::fromAngle(-135)));
        
        //Render the radar items
        queue.add([](){
            glStencilFunc(GL_EQUAL, 1, 0xff);
            glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
        });
        data.color = sp::Color(1, 0, 0);
        queue.add(sp::Matrix4x4f::translate(1, 0, 0) * sp::Matrix4x4f::scale(1.0/scale, 1.0/scale, 1), data);

        queue.add([](){
            glDisable(GL_STENCIL_TEST);
        });
        queue.setCamera(node->getScene()->getCamera());
    }else{
        sp::BasicNodeRenderPass::addNodeToRenderQueue(queue, node);
    }
}