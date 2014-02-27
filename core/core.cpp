#ifndef CORE_H
#define CORE_H

#include "common/Fortress.h"
#include "common/World.h"

#include "core/Fortress.h"

class Chunk : public IChunk {

public:
    inline Tile &operator()(int x, int y)
    {
        return m_Tiles[y * CHUNK_SIZE + x];
    }

};

class World : public IWorld {

public:
    const std::shared_ptr<IChunk> getChunk(int X, int Y);

};

const std::shared_ptr<IChunk> World::getChunk(int X, int Y)
{
    return std::make_shared<Chunk>();
}

IFortress *IFortress::getFortress(const char *ui_version)
{
    return new Fortress(ui_version);
}

#endif
