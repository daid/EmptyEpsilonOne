#pragma once

#include "../spaceObject/craft.h"
#include <sp2/graphics/gui/widget/widget.h>

class RadarWidget : public sp::gui::Widget
{
public:
    RadarWidget(sp::P<sp::gui::Widget> parent);

    virtual void setAttribute(const sp::string &key, const sp::string &value) override;

    virtual bool onPointerDown(sp::io::Pointer::Button button, sp::Vector2d position, int id) override;
    virtual void onPointerDrag(sp::Vector2d position, int id) override;
    virtual void onPointerUp(sp::Vector2d position, int id) override;

    virtual void updateRenderData() override;

    virtual void onUpdate(float delta) override;

    void setOwnerCraft(sp::P<Craft> owner) { owner_craft = owner; }
    void setOnClick(std::function<void(sp::Vector2d)> func) { on_click = func; }
    void setOnDrag(std::function<void(sp::Vector2d)> func) { on_drag = func; }

    sp::Vector2d getViewTargetPosition() { return view_position; }
    double getViewTargetRotation() { return view_rotation; }
    double getRange() { return range; }
private:
    sp::Vector2d widgetPositionToWorld(sp::Vector2d position);

    enum class Shape
    {
        Circle,
        Rectangle,
    } shape = Shape::Circle;
    enum class RangeType
    {
        Fixed,
        Short,
        Long,
    } range_type = RangeType::Short;
    double range = 5000.0;
    bool ghostdots = false;
    bool waypoints = false;
    bool callsigns = false;
    bool heading_indicators = false;
    bool tube_indicators = false;

    sp::P<Craft> owner_craft;
    std::function<void(sp::Vector2d)> on_click;
    std::function<void(sp::Vector2d)> on_drag;

    sp::Vector2d view_position;
    double view_rotation{90.0};
};
