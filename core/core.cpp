#ifndef CORE_H
#define CORE_H

#include "common/World.h"

class CoreChunk : public Chunk {

public:
    inline Tile &operator()(int x, int y)
    {
        return m_Tiles[y * CHUNK_SIZE + x];
    }

};

class CoreWorld : public World {

public:
    const std::shared_ptr<Chunk> getChunk(int X, int Y);

};

const std::shared_ptr<Chunk> CoreWorld::getChunk(int X, int Y)
{
    return std::make_shared<CoreChunk>();
}

#endif
