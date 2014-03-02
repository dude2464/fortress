#include "core/World.h"

#include <algorithm>
#include <iterator>

IEntity::~IEntity()
{
}

std::list<std::shared_ptr<const IEntity> > Chunk::entities()
{
    typedef std::unordered_map<
            Coordinates,
            std::shared_ptr<Entity> >::value_type map_element;

    // Copies from unordered_map to list
    // Somehow unordered_map<A, shared_ptr<B> >& doesn't cast to
    // unordered_map<A, shared_ptr<const C> >& (with B subclass of C)
    std::list<std::shared_ptr<const IEntity> > result(m_Entities.size());
    std::transform(m_Entities.begin(), m_Entities.end(),
                   std::back_inserter(result),
                   [](map_element &v){
                       return v.second;
                   });
    return result;
}

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
