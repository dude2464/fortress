#include <QPainter>
#include <QPaintEvent>

#include "common/Fortress.h"
#include "common/World.h"

#include "ui_qt/GameCanvas.h"

GameCanvas::GameCanvas(IGame *game)
    : m_Game(game), m_Position(1000, -289, 0)
{
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

QSize GameCanvas::sizeHint()
{
    return QSize(800, 800);
}

int mod(int a, int b)
{
    if(a >= 0)
        return a % b;
    else
        return b - 1 - (-a - 1) % b;
}

void GameCanvas::paintEvent(QPaintEvent *event)
{
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

    painter.setPen(Qt::NoPen);

    for(int y = screencorner.y; y < screencorner.y + 40; ++y)
    {
        for(int x = screencorner.x; x < screencorner.x + 40; ++x)
        {
            ChunkCoordinates chunk = Coordinates(
                    x, y, m_Position.z).chunk();
            int xi = (chunk.X > topleft.X)?1:0;
            int yi = (chunk.Y > topleft.Y)?2:0;
            Coordinates chunk_topleft(chunk);
            Tile t = (*chunks[xi + yi])(x - chunk_topleft.x,
                                        y - chunk_topleft.y,
                                        m_Position.z - chunk_topleft.z);
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
