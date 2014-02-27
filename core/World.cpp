#include "core/World.h"

const std::shared_ptr<IChunk> World::getChunk(int X, int Y)
{
    return std::make_shared<Chunk>();
}
