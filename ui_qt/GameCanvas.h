#ifndef UIQT_GAMECANVAS_H
#define UIQT_GAMECANVAS_H

#include <QWidget>

#include "common/Fortress.h"

/**
 * The central zone that shows a game's world.
 *
 * This is tied to an IGame, and is destroyed when that game is terminated.
 */
class GameCanvas : public QWidget {

    Q_OBJECT

public:
    GameCanvas(IGame *game);

};

#endif
