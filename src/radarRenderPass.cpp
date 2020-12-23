#include "radarRenderPass.h"

#include <sp2/scene/camera.h>
#include <sp2/scene/scene.h>
#include <sp2/graphics/opengl.h>
#include <sp2/graphics/meshdata.h>
#include <sp2/graphics/textureManager.h>
#include "gui/radar.h"
#include "spaceObject/spaceObject.h"


void RadarRenderPass::addNodeToRenderQueue(sp::RenderQueue& queue, sp::P<sp::Node>& node)
{
    if (node->render_data.type == sp::RenderData::Type::Custom1)
    {
        sp::P<RadarWidget> radar_widget = node;
        auto view_position = radar_widget->getViewTargetPosition();
        
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
        data.color = sp::Color(0.1, 0.1, 0.1);
        queue.add(sp::Matrix4x4f::identity(), data);

        float scale = 5000 / std::min(radar_widget->getRenderSize().x, radar_widget->getRenderSize().y);
        queue.setCamera(node->getScene()->getCamera()->getProjectionMatrix(), sp::Matrix4x4f::scale(1.0/scale, 1.0/scale, 1));
        
        //Render the radar items
        queue.add([](){
            glStencilFunc(GL_EQUAL, 1, 0xff);
            glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
        });

        queue.setCamera(node->getScene()->getCamera()->getProjectionMatrix(), sp::Matrix4x4f::scale(1.0/scale,1.0/scale,1) * sp::Matrix4x4f::translate(-view_position.x, -view_position.y, 0) * sp::Matrix4x4f::fromQuaternion(sp::Quaternionf::fromAngle(0)));
        //TODO: Render radar background

        auto scene = sp::Scene::get("SCENE_1");
        for(auto node : scene->getRoot()->getChildren())
        {
            sp::P<SpaceObject> obj = node;
            obj->renderOnRadar(queue);
        }

        queue.add([](){
            glDisable(GL_STENCIL_TEST);
        });
        queue.setCamera(node->getScene()->getCamera());
    }else{
        sp::BasicNodeRenderPass::addNodeToRenderQueue(queue, node);
    }
}