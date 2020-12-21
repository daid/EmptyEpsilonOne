#include "scenarioSelectionMenu.h"
#include "mainMenu.h"
#include "shipSelectionMenu.h"
#include "../version.h"
#include "../multiplayer.h"
#include "../scenarioInfo.h"
#include "../scenario.h"

#include <sp2/graphics/gui/loader.h>
#include <sp2/graphics/gui/widget/itemlist.h>

void openScenarioSelectionMenu()
{
    auto scenarios = std::make_shared<std::vector<ScenarioInfo>>(std::move(ScenarioInfo::getAll()));

    auto menu = sp::gui::Loader::load("gui/menus/scenario_selection.gui", "MAIN");
    sp::P<sp::gui::ItemList> category = menu->getWidgetWithID("CATEGORY");
    sp::P<sp::gui::ItemList> scenario = menu->getWidgetWithID("SCENARIO");
    sp::P<sp::gui::ItemList> variation = menu->getWidgetWithID("VARIATION");
    auto description = menu->getWidgetWithID("DESCRIPTION");
    sp::string prev_category;
    for (const auto &s : *scenarios)
    {
        if (s.category == prev_category)
            continue;
        category->addItem(s.category, s.category);
        prev_category = s.category;
    }

    auto update_description = [=](sp::Variant v) mutable {
        description->setAttribute("text", "");

        for (const auto &s : *scenarios)
        {
            if (s.resource_name == scenario->getItemData(scenario->getSelectedIndex()))
            {
                auto desc = "Author: " + s.author + "\n" + s.description;
                menu->getWidgetWithID("START")->setEnable(s.required_version <= empty_epsilon_version);
                if (s.required_version > empty_epsilon_version)
                    desc = "Requires EE version: " + sp::string(s.required_version) + "\n" + desc;
                if (!s.variations.empty())
                    desc += "\n" + s.variations[variation->getSelectedIndex()].second;
                description->setAttribute("text", desc);
            }
        }
    };
    auto update_variation_list = [=](sp::Variant v) mutable {
        variation->clearItems();
        for (const auto &s : *scenarios)
            if (s.resource_name == scenario->getItemData(scenario->getSelectedIndex()))
                for (const auto &v : s.variations)
                    variation->addItem(v.first, v.first);
        update_description(0);
    };
    auto update_scenario_list = [=](sp::Variant v) mutable {
        scenario->clearItems();
        for (const auto &s : *scenarios)
            if (s.category == category->getItemData(category->getSelectedIndex()))
                scenario->addItem(s.name, s.resource_name);
        update_variation_list(0);
    };
    category->setEventCallback(update_scenario_list);
    scenario->setEventCallback(update_variation_list);
    variation->setEventCallback(update_description);
    update_scenario_list(0);

    menu->getWidgetWithID("CLOSE")->setEventCallback([=](sp::Variant v) mutable {
        closeClientOrServer();
        menu.destroy();
        openMainMenu();
    });
    menu->getWidgetWithID("START")->setEventCallback([=](sp::Variant v) mutable {
        //TODO: Variation
        startScenario(scenario->getItemData(scenario->getSelectedIndex()));

        menu.destroy();
        openShipSelectionMenu();
    });
}
