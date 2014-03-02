#ifndef CORE_FORTRESS_H
#define CORE_FORTRESS_H

#include "common/Fortress.h"
#include "common/World.h"

class World;

class Game : public IGame {

private:
    World *m_World;

public:
    Game();
    ~Game();
    IWorld *world();
    IMode *dig();

};

class Fortress : public IFortress {

public:
    Fortress(const char *ui_version);
    IGame *newGame(const GameParameters &params);

};

class DesignateMode : public IMode {

private:
    Game *m_Game;
    Designation m_Designation;

public:
    DesignateMode(Game *game, Designation designation);
    InputMode inputMode() const;
    bool areaSelected(const Coordinates &topleft,
                      const Coordinates &bottomright);

};

#endif
