#include "mainMenu.h"
#include "scenarioSelectionMenu.h"
#include "../multiplayer.h"
#include "../version.h"

#include <sp2/graphics/gui/loader.h>
#include <sp2/engine.h>


void openMainMenu()
{
    auto menu = sp::gui::Loader::load("gui/menus/main.gui", "MAIN");
    menu->getWidgetWithID("VERSION")->setAttribute("label", "Version: " + sp::string(empty_epsilon_version));
    //TODO: Update username from the textfield
    //menu->getWidgetWithID("USERNAME")
    menu->getWidgetWithID("SERVER")->setEventCallback([=](sp::Variant v) mutable
    {
        if (startServer())
        {
            menu.destroy();
            openScenarioSelectionMenu();
        }
    });
    menu->getWidgetWithID("CLIENT")->setEventCallback([=](sp::Variant v) mutable
    {
        //new ServerBrowserMenu(ServerBrowserMenu::Local);
        //menu.destroy();
    });
    menu->getWidgetWithID("OPTIONS")->setEventCallback([=](sp::Variant v) mutable
    {
        //new OptionsMenu();
        //menu.destroy();
    });
    menu->getWidgetWithID("QUIT")->setEventCallback([=](sp::Variant v) mutable
    {
        sp::Engine::getInstance()->shutdown();
    });

    menu->getWidgetWithID("TUTORIAL")->setEventCallback([=](sp::Variant v) mutable
    {
        //new TutorialMenu();
        //menu.destroy();
    });

    menu->getWidgetWithID("DEBUG_WIDGET_SHOWCASE")->setEventCallback([=](sp::Variant v) mutable
    {
        auto showcase = sp::gui::Loader::load("gui/menus/debug_widget_showcase.gui", "SHOWCASE", nullptr, true);
        showcase->getWidgetWithID("SLIDER")->setEventCallback([=](sp::Variant v2) mutable
        {
            showcase->getWidgetWithID("PROGRESSBAR")->setAttribute("value", sp::string(v2.getDouble()));
            showcase->getWidgetWithID("PROGRESSBAR2")->setAttribute("value", sp::string(v2.getDouble()));
            showcase->getWidgetWithID("PROGRESSBAR3")->setAttribute("value", sp::string(v2.getDouble()));
            showcase->getWidgetWithID("PROGRESSBAR4")->setAttribute("value", sp::string(v2.getDouble()));
            showcase->getWidgetWithID("PROGRESSBAR5")->setAttribute("value", sp::string(v2.getDouble()));
        });
        menu.destroy();
    });
#ifdef DEBUG
    menu->getWidgetWithID("DEBUG_WIDGET_SHOWCASE")->show();
#endif

    //TODO: touchscreen calib
    //TODO: credits
    //TODO: instance name
    //TODO: Debug direct to GM
}
