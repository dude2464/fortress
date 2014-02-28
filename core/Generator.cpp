#include "core/Generator.h"
#include "core/World.h"

Generator::Generator(unsigned long seed)
  : m_Seed(seed)
{
}

std::shared_ptr<Chunk> Generator::generate(int X, int Y, int Z)
{
    Chunk *chunk = new Chunk();

    Tile tile;
    if(Z >= 0)
        tile = Tile::AIR;
    else
        tile = Tile::ROCK;

    for(int x = 0; x < CHUNK_SIZE; ++x)
        for(int y = 0; y < CHUNK_SIZE; ++y)
            for(int z = 0; z < CHUNK_DEPTH; z++)
                (*chunk)(x, y, z) = tile;

    return std::shared_ptr<Chunk>(chunk);
}
