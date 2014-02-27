#ifndef CORE_WORLD_H
#define CORE_WORLD_H

#include "common/World.h"

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

#endif
