#include "scenarioSelectionMenu.h"
#include "mainMenu.h"
#include "shipSelectionMenu.h"
#include "../multiplayer.h"

#include <sp2/graphics/gui/loader.h>

//TMP, hard coded scenario creation
#include "../spaceScene.h"
#include "../spaceObject/asteroid.h"
#include "../spaceObject/playerCraft.h"

void openScenarioSelectionMenu()
{
    auto menu = sp::gui::Loader::load("gui/menus/scenario_selection.gui", "MAIN");
    menu->getWidgetWithID("CLOSE")->setEventCallback([=](sp::Variant v) mutable
    {
        closeClientOrServer();
        menu.destroy();
        openMainMenu();
    });
    menu->getWidgetWithID("START")->setEventCallback([=](sp::Variant v) mutable
    {
        //TODO: start scenario script instead of hard coding
        auto scene = new SpaceScene("SCENE_1");
        auto a = new Asteroid(scene->getRoot());
        a->setPosition(sp::Vector2d(1000, 1000));
        for(int n=0; n<5000; n+=100)
        {
            a = new Asteroid(scene->getRoot());
            a->setPosition(sp::Vector2d(n, 0));
        }
        auto player = new PlayerCraft(scene->getRoot());
        player->setPosition(sp::Vector2d(100, 100));

        menu.destroy();
        openShipSelectionMenu();
    });
}
