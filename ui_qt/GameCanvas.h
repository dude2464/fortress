#ifndef UIQT_GAMECANVAS_H
#define UIQT_GAMECANVAS_H

#include <QWidget>

#include "common/World.h"

class IGame;

/**
 * The central zone that shows a game's world.
 *
 * This is tied to an IGame, and is destroyed when that game is terminated.
 */
class GameCanvas : public QWidget {

    Q_OBJECT

private:
    IGame *m_Game;
    Coordinates m_Position; // Current position of camera

protected:
    void paintEvent(QPaintEvent *event);

public:
    GameCanvas(IGame *game);
    QSize sizeHint();

};

#endif
