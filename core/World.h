#ifndef CORE_WORLD_H
#define CORE_WORLD_H

#include <unordered_map>

#include "common/Vector.h"
#include "common/World.h"

#include "core/Generator.h"

class Chunk : public BaseChunk<Tile> {
};

class DesignationChunk : public BaseChunk<Designation> {
};

class World : public IWorld {

private:
    Generator m_Generator;
    std::unordered_map<ChunkCoordinates, std::shared_ptr<Chunk> > m_Chunks;

public:
    World(unsigned long seed);
    std::shared_ptr<IChunk> getChunk(const ChunkCoordinates &chunk);
    std::shared_ptr<IDesignationChunk> getDesignationChunk(
            const ChunkCoordinates &chunk);

};

#endif
