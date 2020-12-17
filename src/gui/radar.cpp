#include <sp2/stringutil/convert.h>
#include <sp2/graphics/shader.h>
#include <sp2/graphics/meshdata.h>
#include <sp2/graphics/textureManager.h>
#include "radar.h"

SP_REGISTER_WIDGET("radar", RadarWidget);

RadarWidget::RadarWidget(sp::P<sp::gui::Widget> parent)
    : sp::gui::Widget(parent)
{
}

void RadarWidget::setAttribute(const sp::string &key, const sp::string &value)
{
    if (key == "shape")
    {
        if (value == "circle")
            shape = Shape::Circle;
        else if (value == "rectangle")
            shape = Shape::Rectangle;
        markRenderDataOutdated();
    }
    else if (key == "range")
    {
        if (value == "short")
        {
            range_type = RangeType::Short;
        }
        else if (value == "long")
        {
            range_type = RangeType::Long;
        }
        else
        {
            range_type = RangeType::Fixed;
            range = sp::stringutil::convert::toFloat(value);
        }
    }
    else if (key == "ghostdots")
    {
        ghostdots = sp::stringutil::convert::toBool(value);
    }
    else if (key == "waypoints")
    {
        waypoints = sp::stringutil::convert::toBool(value);
    }
    else if (key == "callsigns")
    {
        callsigns = sp::stringutil::convert::toBool(value);
    }
    else if (key == "headingIndicators")
    {
        heading_indicators = sp::stringutil::convert::toBool(value);
    }
    else if (key == "tubeIndicators")
    {
        tube_indicators = sp::stringutil::convert::toBool(value);
    }
    else
    {
        sp::gui::Widget::setAttribute(key, value);
    }
}

void RadarWidget::updateRenderData()
{
    if (shape == Shape::Circle)
    {
        render_data.texture = sp::texture_manager.get("gui/radar/circle_overlay.png");
        render_data.shader = sp::Shader::get("internal:basic.shader");

        sp::MeshData::Vertices vertices;
        sp::MeshData::Indices indices{0, 1, 2, 2, 1, 3};
        vertices.reserve(4);

        auto render_size = getRenderSize();
        vertices.emplace_back(sp::Vector3f(0, 0, 0), sp::Vector2f(0, 1));
        vertices.emplace_back(sp::Vector3f(render_size.x, 0, 0), sp::Vector2f(1, 1));
        vertices.emplace_back(sp::Vector3f(0, render_size.y, 0), sp::Vector2f(0, 0));
        vertices.emplace_back(sp::Vector3f(render_size.x, render_size.y, 0), sp::Vector2f(1, 0));

        render_data.mesh = sp::MeshData::create(std::move(vertices), std::move(indices));
    }
    else
    {
        render_data.shader = nullptr;
    }
}

void RadarWidget::onUpdate(float delta)
{
    sp::gui::Widget::onUpdate(delta);
}