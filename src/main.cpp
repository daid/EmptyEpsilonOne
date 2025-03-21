#include <sp2/engine.h>
#include <sp2/window.h>
#include <sp2/logging.h>
#include <sp2/io/resourceProvider.h>
#include <sp2/graphics/gui/scene.h>
#include <sp2/graphics/gui/theme.h>
#include <sp2/graphics/gui/loader.h>
#include <sp2/graphics/scene/graphicslayer.h>
#include <sp2/graphics/scene/basicnoderenderpass.h>
#include <sp2/graphics/scene/collisionrenderpass.h>
#include <sp2/graphics/textureManager.h>
#include <sp2/scene/scene.h>
#include <sp2/scene/node.h>
#include <sp2/scene/camera.h>
#include <sp2/io/keybinding.h>

#include "menus/mainMenu.h"
#include "gameGlobalInfo.h"
#include "spaceScene.h"
#include "radarRenderPass.h"
#include "gui/radar.h"


int empty_epsilon_version = 1;

sp::P<sp::Window> window;

int main(int argc, char **argv)
{
    sp::P<sp::Engine> engine = new sp::Engine();
    SP_REGISTER_WIDGET("radar", RadarWidget);

    //Create resource providers, so we can load things.
    sp::io::ResourceProvider::createDefault();

    //Disable or enable smooth filtering by default, enabling it gives nice smooth looks, but disabling it gives a more pixel art look.
    sp::texture_manager.setDefaultSmoothFiltering(true);

    //Create a window to render on, and our engine.
    window = new sp::Window(4.0 / 3.0);
#if !defined(DEBUG) && !defined(EMSCRIPTEN)
    window->setFullScreen(true);
#endif

    sp::gui::Theme::loadTheme("default", "gui/theme/basic.theme.txt");
    new sp::gui::Scene(sp::Vector2d(1200, 900));

    sp::P<sp::SceneGraphicsLayer> scene_layer = new sp::SceneGraphicsLayer(1);
    scene_layer->addRenderPass(new RadarRenderPass());
#ifdef DEBUG
    scene_layer->addRenderPass(new sp::CollisionRenderPass());
#endif
    window->addLayer(scene_layer);

    //Create default scenes that always need to be there.
    new GameGlobalInfo();

    openMainMenu();

    engine->run();

    return 0;
}
