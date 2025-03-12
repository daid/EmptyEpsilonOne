#include <sp2/stringutil/convert.h>
#include <sp2/graphics/shader.h>
#include <sp2/graphics/meshdata.h>
#include <sp2/graphics/textureManager.h>

#include "radar.h"


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

bool RadarWidget::onPointerDown(sp::io::Pointer::Button button, sp::Vector2d position, int id)
{
    if (shape == Shape::Circle)
    {
        auto size = getRenderSize();
        auto radius = std::min(size.x, size.y) * 0.5;
        if ((position - size * 0.5).length() > radius)
            return false;
    }
    if (on_click)
        on_click(widgetPositionToWorld(position));
    onPointerDrag(position, id);
    return true;
}

void RadarWidget::onPointerDrag(sp::Vector2d position, int id)
{
    if (on_drag)
        on_drag(widgetPositionToWorld(position));
}

void RadarWidget::onPointerUp(sp::Vector2d position, int id)
{
}

void RadarWidget::updateRenderData()
{
    //render_data.texture = sp::texture_manager.get("gui/radar/circle_overlay.png");
    render_data.shader = sp::Shader::get("internal:color.shader");

    if (shape == Shape::Circle)
        render_data.mesh = sp::MeshData::createCircle(std::min(getRenderSize().x, getRenderSize().y) * 0.5, 64, false);
    else
        render_data.mesh = sp::MeshData::createQuad(sp::Vector2f(getRenderSize()));
}

void RadarWidget::onUpdate(float delta)
{
    sp::gui::Widget::onUpdate(delta);
    if (render_data.type == sp::RenderData::Type::Normal)
        render_data.type = sp::RenderData::Type::Custom1;
    
    if (owner_craft)
    {
        view_position = owner_craft->getPosition2D();
        view_rotation = owner_craft->getRotation2D() - 90;
        switch(range_type)
        {
        case RangeType::Fixed: break;
        case RangeType::Short: range = owner_craft->sensors.short_range; break;
        case RangeType::Long: range = owner_craft->sensors.long_range; break;
        }
    }
}

sp::Vector2d RadarWidget::widgetPositionToWorld(sp::Vector2d position)
{
    position -= getRenderSize() * 0.5;
    position = position.rotate(view_rotation);
    return view_position + position / (std::min(getRenderSize().x, getRenderSize().y) * 0.5) * range;
}
