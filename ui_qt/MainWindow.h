#ifndef UIQT_MAINWINDOW_H
#define UIQT_MAINWINDOW_H

#include <QDialog>
#include <QMainWindow>

#include "common/Fortress.h"

#include "ui_qt/GameCanvas.h"

/**
 * The dialog that pops up to create a new game.
 *
 * Builds the GameParameters that is passed to the core to create the new game.
 */
class NewGameDialog : public QDialog {

    Q_OBJECT

public:
    NewGameDialog();
    GameParameters gameParameters() const;

};

/**
 * The game's main window, in which the game canvas is shown.
 */
class MainWindow : public QMainWindow {

    Q_OBJECT

private:
    IGame *m_Game;
    GameCanvas *m_GameCanvas;

public:
    MainWindow();

public slots:
    void about();
    void newGame();

protected:
    bool maybeSaveGame();

};

extern IFortress *fortress;

#endif
