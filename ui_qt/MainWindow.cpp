#include <QApplication>
#include <QDialogButtonBox>
#include <QMenuBar>
#include <QMessageBox>
#include <QTextCodec>
#include <QVBoxLayout>

#include "logging/logging.h"

#include "ui_qt/MainWindow.h"
#include "ui_qt/config.h"

IFortress *fortress = nullptr;

NewGameDialog::NewGameDialog()
{
    setWindowTitle(tr("New game configuration"));
    // TODO : new game dialog UI

    setLayout(new QVBoxLayout());

    QDialogButtonBox *buttons = new QDialogButtonBox(
            QDialogButtonBox::Yes | QDialogButtonBox::No);
    layout()->addWidget(buttons);
    connect(buttons, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttons, SIGNAL(rejected()), this, SLOT(reject()));
}

GameParameters NewGameDialog::gameParameters() const
{
    return GameParameters();
}

MainWindow::MainWindow()
  : m_Game(nullptr), m_GameCanvas(nullptr)
{
    setWindowTitle(tr("Fortress"));

    QWidget *widget = new QWidget();
    setCentralWidget(widget);

    {
        QMenu *file = menuBar()->addMenu(tr("&Game"));
        QAction *new_game = file->addAction(tr("&New game..."));
        connect(new_game, SIGNAL(triggered()), this, SLOT(newGame()));
        QAction *quit = file->addAction(tr("&Quit"));
        connect(quit, SIGNAL(triggered()), qApp, SLOT(quit()));
    }
    {
        QMenu *help = menuBar()->addMenu(tr("&Help"));
        QAction *aboutQt = help->addAction(tr("About &Qt"));
        connect(aboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
        QAction *about = help->addAction(tr("&About Fortress"));
        connect(about, SIGNAL(triggered()), this, SLOT(about()));
    }
}

void MainWindow::about()
{
    QMessageBox::information(this, tr("About Fortress..."),
        tr("Fortress is a game created by Rémi \"Remram\" Rampin, "
           "<remirampin@gmail.com>\n"
           "See https://github.com/remram44/fortress"));
}

void MainWindow::newGame()
{
    // Save previous game
    if(m_Game != NULL)
    {
        if(!maybeSaveGame())
            return ;
    }

    // Configure through dialog
    NewGameDialog *dialog = new NewGameDialog();
    if(dialog->exec() != QDialog::Accepted)
        return ;
    GameParameters params = dialog->gameParameters();

    // Destroy previous game
    if(m_Game != NULL)
    {
        if(!maybeSaveGame())
            return ;
        delete m_Game;
        m_GameCanvas->deleteLater();
    }

    m_Game = fortress->newGame(params);
    m_GameCanvas = new GameCanvas(m_Game);
    setCentralWidget(m_GameCanvas);
}

bool MainWindow::maybeSaveGame()
{
    // TODO : if the game needs saving, ask and save
    return true;
}

int main(int argc, char **argv)
{
    // Sets up logger
    logging.addOutput(std::make_shared<ConsoleOutput>());
    logging.addOutput(std::make_shared<FileOutput>("fortress.log"));

    // Starts up the core
    fortress = IFortress::getFortress("Qt UI v" UIQT_VERSION_STRING);

    // Starts up Qt
    QApplication app(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    MainWindow *window = new MainWindow();
    window->show();
    return app.exec();
}
