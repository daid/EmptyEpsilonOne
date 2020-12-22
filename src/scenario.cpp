#include "scenario.h"

#include "spaceScene.h"
#include "spaceObject/asteroid.h"
#include "spaceObject/playerCraft.h"

#include <sp2/random.h>
#include <sp2/script/environment.h>

static sp::P<sp::script::Environment> scenario_script_environment;
static sp::P<SpaceScene> scenario_main_scene;

static sp::P<Asteroid> luaNewAsteroid(sp::Vector2d position)
{
    auto result = new Asteroid(scenario_main_scene->getRoot());
    result->setPosition(position);
    return result;
}

static sp::P<PlayerCraft> luaNewPlayerCraft(sp::Vector2d position)
{
    auto result = new PlayerCraft(scenario_main_scene->getRoot());
    result->setPosition(position);
    return result;
}

void startScenario(const sp::string &resource_name)
{
    scenario_main_scene.destroy();
    scenario_main_scene = new SpaceScene("SCENE_1");

    scenario_script_environment.destroy();
    scenario_script_environment = new sp::script::Environment();

    scenario_script_environment->setGlobal("random", sp::random);
    scenario_script_environment->setGlobal("irandom", sp::irandom);
    scenario_script_environment->setGlobal("chance", sp::chance);

    scenario_script_environment->setGlobal("Asteroid", luaNewAsteroid);
    scenario_script_environment->setGlobal("PlayerCraft", luaNewPlayerCraft);

    scenario_script_environment->load(resource_name);
    scenario_script_environment->call("init");
}
