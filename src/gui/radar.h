#pragma once

#include <sp2/graphics/gui/widget/widget.h>

class RadarWidget : public sp::gui::Widget
{
public:
    RadarWidget(sp::P<sp::gui::Widget> parent);

    virtual void setAttribute(const sp::string &key, const sp::string &value) override;

    virtual void updateRenderData() override;

    virtual void onUpdate(float delta) override;

private:
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
    float range = 5000.0;
    bool ghostdots = false;
    bool waypoints = false;
    bool callsigns = false;
    bool heading_indicators = false;
    bool tube_indicators = false;
};
