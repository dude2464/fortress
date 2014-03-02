#include <sstream>

#include "logging/logging.h"

#include "core/Dwarf.h"
#include "core/Fortress.h"
#include "core/World.h"

IGame::~IGame()
{
}

IFortress::~IFortress()
{
}

Game::Game()
{
    logging.log("Starting new game");
    logging.log("Creating world");
    m_World = new World(42);
    logging.log("Spawning dwarves");
    Coordinates spawn(0, 0, 0);
    Coordinates positions[] = {
        spawn,
        Coordinates(spawn.x + 2, spawn.y, spawn.z),
        Coordinates(spawn.x - 2, spawn.y, spawn.z),
        Coordinates(spawn.x, spawn.y + 3, spawn.z),
        Coordinates(spawn.x, spawn.y - 3, spawn.z)
    };
    for(int i = 0; i < 5; ++i)
    {
        std::ostringstream name;
        name << "Dwarf #" << i;
        Dwarf(m_World, positions[i], name.str());
    }
}

Game::~Game()
{
    delete m_World;
}

IWorld *Game::world()
{
    return m_World;
}

IMode *Game::dig()
{
    return new DesignateMode(this, Designation::DIG);
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

DesignateMode::DesignateMode(Game *game, Designation designation)
  : m_Game(game), m_Designation(designation)
{
}

IMode::InputMode DesignateMode::inputMode() const
{
    return InputMode::DRAW_AREA;
}

bool DesignateMode::areaSelected(const Coordinates &topleft,
                                 const Coordinates &bottomright)
{
    ChunkCoordinates poschunk = topleft.chunk();
    const ChunkCoordinates endchunk = bottomright.chunk();
    for(; poschunk.Z <= endchunk.Z; ++poschunk.Z)
    {
        for(; poschunk.Y <= endchunk.Y; ++poschunk.Y)
        {
            for(; poschunk.X <= endchunk.X; ++poschunk.X)
            {
                std::shared_ptr<IDesignationChunk> dchunk =
                        m_Game->world()->getDesignationChunk(poschunk);
                Coordinates pos = vec_max(topleft, Coordinates(poschunk));
                const Coordinates end = vec_min(
                        bottomright,
                        Coordinates(ChunkCoordinates(poschunk.X+1,
                                                     poschunk.Y+1,
                                                     poschunk.Z+1)));

                for(; pos.z < end.z; ++pos.z)
                {
                    for(; pos.y < end.y; ++pos.y)
                    {
                        for(; pos.x < end.x; ++pos.x)
                        {
                            (*dchunk)(pos) = m_Designation;
                        }
                    }
                }
            }
        }
    }
    return true;
}
