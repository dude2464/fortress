#ifndef UIQT_MAINWINDOW_H
#define UIQT_MAINWINDOW_H

#include <QMainWindow>

class MainWindow : public QMainWindow {

    Q_OBJECT

public:
    MainWindow();

public slots:
    void about();

};

#endif
