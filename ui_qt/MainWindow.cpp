#include <QApplication>
#include <QMenuBar>
#include <QMessageBox>
#include <QTextCodec>

#include "MainWindow.h"

MainWindow::MainWindow()
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

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    MainWindow *window = new MainWindow();
    window->show();
    return app.exec();
}
