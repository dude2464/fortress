#include <QApplication>
#include <QDialog>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QLabel>
#include <QPainter>
#include <QPaintEvent>

#include "perlin/test.h"

#include <iostream>

RenderingWidget::RenderingWidget()
  : m_X(0), m_Y(0), m_Z(0)
{
    setFocusPolicy(Qt::StrongFocus);
    setFixedSize(800, 800);
    m_Noise = new PerlinNoise3D(1.0f/16.0f, 0.750f, 8);
}

void RenderingWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    for(int y = 0; y < 160; ++y)
    {
        for(int x = 0; x < 160; ++x)
        {
            float f = m_Noise->sample(m_X + x, m_Y + y, m_Z);
            int n = int((f + 1.0f) * 128.0f);
            if(n < 0)
                n = 0;
            else if(n > 255)
                n = 255;

            painter.setBrush(QColor(n, n, n));
            painter.drawRect(x*5, y*5, 4, 4);
        }
    }
}

void RenderingWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Left)
        m_X -= 1;
    else if(event->key() == Qt::Key_Right)
        m_X += 1;
    else if(event->key() == Qt::Key_Up)
        m_Y -= 1;
    else if(event->key() == Qt::Key_Down)
        m_Y += 1;
    else if(event->text() == "<")
        m_Z += 1;
    else if(event->text() == ">")
        m_Z -= 1;
    else
    {
        QWidget::keyPressEvent(event);
        return ;
    }
    repaint();
}

TestWindow::TestWindow()
{
    setWindowTitle(tr("Test Perlin Noise"));
    setLayout(new QHBoxLayout());

    m_Render = new RenderingWidget();
    layout()->addWidget(m_Render);

    setFixedSize(sizeHint());
}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    TestWindow *window = new TestWindow();
    window->show();
    return app.exec();
}
