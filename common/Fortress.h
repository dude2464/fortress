#ifndef COMMON_FORTRESS_H
#define COMMON_FORTRESS_H

class GameParameters {
};

class IGame {

public:
    virtual ~IGame();

};

/**
 * Interface for the core, accessible to UIs.
 *
 * A pointer to this interface can be obtained via getFortress().
 */
class IFortress {

public:
    virtual ~IFortress();
    static IFortress *getFortress(const char *ui_version);
    virtual IGame *newGame(const GameParameters &params) = 0;

};

#endif
