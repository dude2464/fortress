#ifndef CORE_WORLD_H
#define CORE_WORLD_H

#include <unordered_map>

#include "common/Vector.h"
#include "common/World.h"

#include "core/Generator.h"

class Entity : public IEntity {
};

class Chunk : public IChunk {

private:
    std::unordered_map<Coordinates, std::shared_ptr<Entity> > m_Entities;

public:
    std::list<std::shared_ptr<const IEntity> > entities();

};

class DesignationChunk : public IDesignationChunk {
};

class World : public IWorld {

private:
    Generator m_Generator;
    std::unordered_map<ChunkCoordinates, std::shared_ptr<Chunk> > m_Chunks;

public:
    World(unsigned long seed);
    std::shared_ptr<const IChunk> getChunk(const ChunkCoordinates &chunk);
    std::shared_ptr<IDesignationChunk> getDesignationChunk(
            const ChunkCoordinates &chunk);

};

#endif
