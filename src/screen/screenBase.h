#pragma once

#include <sp2/graphics/gui/widget/widget.h>
#include "../spaceObject/playerCraft.h"


class ScreenBase : public sp::gui::Widget
{
public:
    ScreenBase(sp::P<sp::gui::Widget> parent, sp::P<PlayerCraft> player, const sp::string& screen_resource_filename);

    void onUpdate(float delta) override;
private:
    void link(sp::P<sp::gui::Widget> widget);

    sp::P<sp::gui::Widget> gui;
    sp::P<PlayerCraft> player;
};