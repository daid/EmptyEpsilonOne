#include "shipSelectionMenu.h"
#include "scenarioSelectionMenu.h"
#include "mainMenu.h"
#include "../multiplayer.h"

#include <sp2/graphics/gui/loader.h>

void openShipSelectionMenu()
{
    auto menu = sp::gui::Loader::load("gui/menus/ship_selection.gui", "MAIN");
    menu->getWidgetWithID("CLOSE")->setEventCallback([=](sp::Variant) mutable
    {
        if (isServer())
        {
            openScenarioSelectionMenu();
        }
        else
        {
            closeClientOrServer();
            openMainMenu();
        }
        menu.destroy();
    });
    menu->getWidgetWithID("JOIN")->setEventCallback([=](sp::Variant) mutable
    {
        sp::gui::Loader::load("gui/screens/helms.gui", "MAIN", nullptr, true);
        menu.destroy();
    });
}
