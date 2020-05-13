#include "scenarioSelectionMenu.h"
#include "mainMenu.h"
#include "shipSelectionMenu.h"

#include <sp2/graphics/gui/loader.h>

void openScenarioSelectionMenu()
{
    auto menu = sp::gui::Loader::load("gui/menus/scenario_selection.gui", "MAIN");
    menu->getWidgetWithID("CLOSE")->setEventCallback([=](sp::Variant v) mutable
    {
        //TODO: destroy server
        menu.destroy();
        openMainMenu();
    });
    menu->getWidgetWithID("START")->setEventCallback([=](sp::Variant v) mutable
    {
        //TODO: start scenario script
        menu.destroy();
        openShipSelectionMenu();
    });
}
