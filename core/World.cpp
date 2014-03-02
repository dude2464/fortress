#include "core/World.h"

World::World(unsigned long seed)
  : m_Generator(seed)
{
}

std::shared_ptr<const IChunk> World::getChunk(const ChunkCoordinates &coords)
{
    // Get chunk from memory
    auto it = m_Chunks.find(coords);
    if(it != m_Chunks.end())
        return it->second;
    // TODO : Get chunk from hard storage
    // Generate new chunk
    std::shared_ptr<Chunk> chunk = m_Generator.generate(coords);
    m_Chunks[coords] = chunk;
    return chunk;
}

std::shared_ptr<IDesignationChunk> World::getDesignationChunk(
        const ChunkCoordinates &chunk)
{
    return std::make_shared<DesignationChunk>();
}
