#ifndef CORE_WORLD_H
#define CORE_WORLD_H

#include <unordered_map>

#include "common/Vector.h"
#include "common/World.h"

#include "core/Generator.h"

class Chunk : public IChunk {

public:
    inline Tile &operator()(int x, int y, int z)
    {
        return m_Tiles[(z * CHUNK_DEPTH + y) * CHUNK_SIZE + x];
    }

};

class World : public IWorld {

private:
    Generator m_Generator;
    std::unordered_map<ChunkCoordinates, std::shared_ptr<Chunk> > m_Chunks;

public:
    World(unsigned long seed);
    std::shared_ptr<IChunk> getChunk(const ChunkCoordinates &chunk);

};

#endif
