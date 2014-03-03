#include <QApplication>
#include <QDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QPainter>

#include "perlin/test.h"

RenderingWidget::RenderingWidget()
{
    setFixedSize(800, 800);
    m_Noise = new PerlinNoise3D(1.0f/16.0f, 0.750f, 8);

    for(int y = 0; y < 160; ++y)
    {
        for(int x = 0; x < 160; ++x)
        {
            float f = m_Noise->sample(x, y, 0.0f);
            int n = int((f + 1.0f) * 128.0f);
            if(n < 0)
                n = 0;
            else if(n > 255)
                n = 255;
            m_Bitmap[y * 160 + x] = n;
        }
    }
}

void RenderingWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    for(int y = 0; y < 160; ++y)
    {
        for(int x = 0; x < 160; ++x)
        {
            int n = m_Bitmap[y * 160 + x];
            painter.setBrush(QColor(n, n, n));
            painter.drawRect(x*5, y*5, 4, 4);
        }
    }
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
