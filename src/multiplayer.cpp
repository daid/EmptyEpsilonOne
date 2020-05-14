#include "multiplayer.h"

#include <sp2/multiplayer/server.h>

static std::unique_ptr<sp::multiplayer::Base> multiplayer_base;

bool startServer()
{
    auto server = new sp::multiplayer::Server("EEO", 1);
    if (!server->listen(30666))
    {
        delete server;
        return false;
    }
    multiplayer_base = std::unique_ptr<sp::multiplayer::Base>(server);
    return true;
}

bool isServer()
{
    return multiplayer_base && multiplayer_base->isServer();
}

void closeClientOrServer()
{
    multiplayer_base = nullptr;
}
