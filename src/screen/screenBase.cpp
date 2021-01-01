#include "screenBase.h"
#include "../gui/radar.h"

#include <sp2/graphics/gui/loader.h>
#include <sp2/graphics/gui/widget/label.h>


class ImpulseControl : public sp::Node
{
public:
    ImpulseControl(sp::P<sp::gui::Widget> parent, sp::P<PlayerCraft> player)
    : sp::Node(parent), player(player)
    {
        parent->setEventCallback([player, parent](sp::Variant v)
        {
            auto value = v.getDouble();
            if (std::abs(value) < 0.1)
            {
                value = 0.0;
                parent->setAttribute("value", "0.0");
            }
            player->commandSetImpulseRequest(value);
        });
    }

    void onUpdate(float delta) override
    {
        sp::P<sp::gui::Widget> w = getParent();
        w->setAttribute("value", sp::string(player->impulse.request));
    }
private:
    sp::P<PlayerCraft> player;
};


class WarpControl : public sp::Node
{
public:
    WarpControl(sp::P<sp::gui::Widget> parent, sp::P<PlayerCraft> player)
    : sp::Node(parent), player(player)
    {
        parent->setEventCallback([player, parent](sp::Variant v)
        {
            auto value = int(v.getDouble() + 0.5);
            parent->setAttribute("value", sp::string(value));
            player->commandSetWarpRequest(value);
        });
    }

    void onUpdate(float delta) override
    {
        sp::P<sp::gui::Widget> w = getParent();
        w->setAttribute("value", sp::string(player->warpdrive.request));
        w->setAttribute("max", sp::string(player->warpdrive.config.max_level));
    }
private:
    sp::P<PlayerCraft> player;
};

class LabelValueDisplay : public sp::Node
{
public:
    LabelValueDisplay(sp::P<sp::gui::Widget> parent, sp::P<PlayerCraft> player, std::function<sp::string(sp::P<PlayerCraft>)> format_func)
    : sp::Node(parent), player(player), format_func(format_func)
    {
    }

    void onUpdate(float delta) override
    {
        if (player)
        {
            sp::P<sp::gui::Widget> w = getParent();
            w->setAttribute("label", format_func(player));
        }
    }
private:
    sp::P<PlayerCraft> player;
    std::function<sp::string(sp::P<PlayerCraft>)> format_func;
};

ScreenBase::ScreenBase(sp::P<sp::gui::Widget> parent, sp::P<PlayerCraft> player, const sp::string& screen_resource_filename)
: sp::gui::Widget(parent), player(player)
{
    layout.fill_width = true;
    layout.fill_height = true;
    gui = sp::gui::Loader::load(screen_resource_filename, "MAIN", this);

    link(gui);
}

void ScreenBase::onUpdate(float delta)
{
    if (!player)
    {
        gui.destroy();
    }
    sp::gui::Widget::onUpdate(delta);
}

void ScreenBase::link(sp::P<sp::gui::Widget> widget)
{
    if (!widget)
        return;
    for(auto child : widget->getChildren())
        link(child);

    if (widget->getID() == "IMPULSE")
        new ImpulseControl(widget, player);
    else if (widget->getID() == "WARP")
        new WarpControl(widget, player);
    
    sp::P<RadarWidget> radar = widget;
    if (radar)
    {
        radar->setOwnerCraft(player);
        radar->setOnDrag([this](sp::Vector2d position) {
            if (player)
                player->commandSetManeuverTarget((position - player->getPosition2D()).angle());
        });
    }

    if (widget->tag == "")
        return;
    if (widget->tag == "impulse.current" && sp::P<sp::gui::Label>(widget))
        new LabelValueDisplay(widget, player, [](sp::P<PlayerCraft> player) { return sp::string(int(player->impulse.current * 100)) + "%"; });
    else if (widget->tag == "warp.current" && sp::P<sp::gui::Label>(widget))
        new LabelValueDisplay(widget, player, [](sp::P<PlayerCraft> player) { return sp::string(player->warpdrive.current, 1); });
    else
        LOG(Debug, "Unknown screen widget tag:", widget->tag);
}
