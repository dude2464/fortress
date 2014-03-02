#ifndef COMMON_FORTRESS_H
#define COMMON_FORTRESS_H

class Coordinates;
class IWorld;

/**
 * A mode.
 *
 * This can be activated by the UI.
 *
 * It could be an action that is waiting for the uesr to select a zone or a
 * target, or something purely graphical. In any case, it is something
 * temporary.
 */
class IMode {

public:
    enum class InputMode {
        //! No input is expected
        NO_INPUT,
        //! The user can draw a rectangle to select a zone
        DRAW_AREA
    };

public:
    /**
     * Indicates how the user can interact in this mode.
     */
    virtual InputMode inputMode() const = 0;
    virtual bool areaSelected(const Coordinates &topleft,
                              const Coordinates &bottomright) = 0;

};

/**
 * Parameters for a new game.
 *
 * This is created by the UI and passed to IFortress::newGame() to start a new
 * game.
 */
class GameParameters {
};

/**
 * Interface on the game.
 */
class IGame {

public:
    virtual ~IGame();
    virtual IWorld *world() = 0;
    virtual IMode *dig() = 0;

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
