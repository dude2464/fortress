#ifndef CORE_FORTRESS_H
#define CORE_FORTRESS_H

#include "common/Fortress.h"

class World;

class Game : public IGame {

private:
    World *m_World;

public:
    Game();
    ~Game();
    IWorld *world();

};


class Fortress : public IFortress {

public:
    Fortress(const char *ui_version);
    IGame *newGame(const GameParameters &params);

};
#endif
