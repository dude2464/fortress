#include "core/Fortress.h"

IGame::~IGame()
{
}

IFortress::~IFortress()
{
}

Fortress::Fortress(const char *ui_version)
{
}

IFortress *IFortress::getFortress(const char *ui_version)
{
    return new Fortress(ui_version);
}

IGame *Fortress::newGame(const GameParameters &params)
{
    // TODO : core newGame
    return nullptr;
}
