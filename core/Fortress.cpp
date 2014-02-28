#include "core/Fortress.h"
#include "core/World.h"

IGame::~IGame()
{
}

IFortress::~IFortress()
{
}

Game::Game()
  : m_World(new World(42))
{
}

Game::~Game()
{
    delete m_World;
}

IWorld *Game::world()
{
    return m_World;
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
    return new Game();
}
