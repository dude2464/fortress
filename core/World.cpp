#include "core/World.h"

World::World(unsigned long seed)
  : m_Generator(seed)
{
}

const std::shared_ptr<IChunk> World::getChunk(int X, int Y, int Z)
{
    // Get chunk from memory
    auto it = m_Chunks.find(Vector3(X, Y, Z));
    if(it != m_Chunks.end())
        return it->second;
    // TODO : Get chunk from hard storage
    // Generate new chunk
    std::shared_ptr<Chunk> chunk = m_Generator.generate(X, Y, Z);
    m_Chunks[Vector3(X, Y, Z)] = chunk;
    return chunk;
}
