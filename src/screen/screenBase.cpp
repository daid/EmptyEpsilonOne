#include "screenBase.h"

#include <sp2/graphics/gui/loader.h>

class ImpulseControl : public sp::Node
{
public:
    ImpulseControl(sp::P<sp::gui::Widget> parent, sp::P<PlayerCraft> player)
    : sp::Node(parent), player(player)
    {
        parent->setEventCallback([player](sp::Variant v)
        {
            player->commandSetImpulseRequest(v.getDouble());
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

ScreenBase::ScreenBase(sp::P<sp::gui::Widget> parent, sp::P<PlayerCraft> player, const sp::string& screen_resource_filename)
: sp::gui::Widget(parent), player(player)
{
    layout.fill_width = true;
    layout.fill_height = true;
    gui = sp::gui::Loader::load(screen_resource_filename, "MAIN", this);

    create<ImpulseControl>("IMPULSE");
}

void ScreenBase::onUpdate(float delta)
{
    if (!player)
    {
        gui.destroy();
    }
    sp::gui::Widget::onUpdate(delta);
}
