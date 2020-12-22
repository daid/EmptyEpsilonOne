#include "shipSelectionMenu.h"
#include "scenarioSelectionMenu.h"
#include "mainMenu.h"
#include "../multiplayer.h"
#include "../spaceObject/playerCraft.h"

#include <sp2/graphics/gui/loader.h>
#include <sp2/graphics/gui/widget/itemlist.h>


class PlayerCraftListUpdater : public sp::Node
{
public:
    PlayerCraftListUpdater(sp::P<sp::gui::ItemList> item_list)
    : sp::Node(item_list), item_list(item_list)
    {
    }

    void onFixedUpdate() override
    {
        auto index = item_list->getSelectedIndex();
        item_list->clearItems();
        for(auto craft : PlayerCraft::all)
            item_list->addItem(sp::string(craft->multiplayer.getId()), sp::string(craft->multiplayer.getId()));
        item_list->setSelectedIndex(index);
    }

private:
    sp::P<sp::gui::ItemList> item_list;
};

void openShipSelectionMenu()
{
    auto menu = sp::gui::Loader::load("gui/menus/ship_selection.gui", "MAIN");
    sp::P<sp::gui::ItemList> screen_list = menu->getWidgetWithID("SCREEN");
    for(const auto& filename : sp::io::ResourceProvider::find("gui/screens/*.gui"))
    {
        sp::string name = filename.substr(filename.rfind("/") + 1);
        name = name.substr(0, name.find(".")).capitalize();
        screen_list->addItem(name, filename);
    }

    menu->getWidgetWithID("CLOSE")->setEventCallback([=](sp::Variant) mutable {
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
    menu->getWidgetWithID("JOIN")->setEventCallback([=](sp::Variant) mutable {
        sp::P<sp::gui::ItemList> ships_list = menu->getWidgetWithID("SHIPS");
        if (ships_list->getSelectedIndex() < 0)
            return;
        sp::P<PlayerCraft> selected_craft;
        for(auto craft : PlayerCraft::all)
            if (sp::string(craft->multiplayer.getId()) == ships_list->getItemData(ships_list->getSelectedIndex()))
                selected_craft = craft;
        if (!selected_craft)
            return;
        auto screen_file = screen_list->getItemData(screen_list->getSelectedIndex());

        sp::gui::Loader::load(screen_file, "MAIN");
        menu.destroy();
    });
    new PlayerCraftListUpdater(menu->getWidgetWithID("SHIPS"));
}
