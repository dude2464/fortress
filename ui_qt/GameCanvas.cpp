#include <QPainter>
#include <QPaintEvent>

#include "logging/logging.h"

#include "common/Fortress.h"
#include "common/World.h"

#include "ui_qt/GameCanvas.h"

GameCanvas::GameCanvas(IGame *game)
  : m_Game(game), m_Position(1000, -289, 0)
{
    setFocusPolicy(Qt::StrongFocus);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

QSize GameCanvas::sizeHint()
{
    return QSize(800, 800);
}

void GameCanvas::paintEvent(QPaintEvent *event)
{
    logging.log(2, "View is at %d;%d;%d",
                m_Position.x, m_Position.y, m_Position.z);
    QPainter painter(this);
    Coordinates screencorner(m_Position.x - 20,
                             m_Position.y - 20,
                             m_Position.z);
    ChunkCoordinates topleft = screencorner.chunk();
    // Pre-load chunks
    std::shared_ptr<IChunk> chunks[] = {
        m_Game->world()->getChunk(topleft.X  , topleft.Y  , topleft.Z),
        m_Game->world()->getChunk(topleft.X+1, topleft.Y  , topleft.Z),
        m_Game->world()->getChunk(topleft.X  , topleft.Y+1, topleft.Z),
        m_Game->world()->getChunk(topleft.X+1, topleft.Y+1, topleft.Z),
    };

    logging.log(2, "Rendering from %d;%d;%d", topleft.X, topleft.Y, topleft.Z);

    painter.setPen(Qt::NoPen);

    for(int y = screencorner.y; y < screencorner.y + 40; ++y)
    {
        for(int x = screencorner.x; x < screencorner.x + 40; ++x)
        {
            ChunkCoordinates chunk = Coordinates(
                    x, y, m_Position.z).chunk();
            int xi = (chunk.X > topleft.X)?1:0;
            int yi = (chunk.Y > topleft.Y)?2:0;
            Tile t = (*chunks[xi + yi])(x, y, m_Position.z);
            switch(t)
            {
            case Tile::AIR:
                painter.setBrush(QColor(127, 127, 127));
                break;
            case Tile::ROCK:
                painter.setBrush(QColor(0, 0, 0));
                break;
            }

            painter.drawRect(20 * (x - screencorner.x),
                             20 * (y - screencorner.y), 20, 20);
        }
    }
}

void GameCanvas::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Left)
        m_Position.x -= 1;
    else if(event->key() == Qt::Key_Right)
        m_Position.x += 1;
    else if(event->key() == Qt::Key_Up)
        m_Position.y -= 1;
    else if(event->key() == Qt::Key_Down)
        m_Position.y += 1;
    else if(event->text() == "<")
        m_Position.z += 1;
    else if(event->text() == ">")
        m_Position.z -= 1;
    else
    {
        QWidget::keyPressEvent(event);
        return ;
    }
    repaint();
}
