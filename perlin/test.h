#ifndef PERLIN_TEST_H
#define PERLIN_TEST_H

#include <QWidget>

#include "perlin/Perlin.h"

class RenderingWidget : public QWidget {

    Q_OBJECT

private:
    PerlinNoise3D *m_Noise;
    int m_Bitmap[160 * 160];

public:
    RenderingWidget();

protected:
    void paintEvent(QPaintEvent *event);

};

class TestWindow : public QWidget {

    Q_OBJECT

private:
    RenderingWidget *m_Render;

public:
    TestWindow();

};

#endif
