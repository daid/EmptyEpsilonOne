#include "shipSelectionMenu.h"

#include <sp2/graphics/gui/loader.h>

void openShipSelectionMenu()
{
    auto menu = sp::gui::Loader::load("gui/menus/ship_selection.gui", "MAIN");
    menu->getWidgetWithID("CLOSE")->setEventCallback([=](sp::Variant v) mutable
    {
        //menu.destroy();
        //if (server) openScenarioSelection
        //else disconnectClient, openMainMenu();
    });
}
