#include <cmath>
#include <random>

#include "logging/logging.h"

#include "common/utils.h"

#include "core/Generator.h"
#include "core/World.h"

Generator::Generator(unsigned long seed)
  : m_Seed(seed)
{
}

std::shared_ptr<Chunk> Generator::generate(const ChunkCoordinates &coords)
{
    logging.log(3, "Generating chunk %d;%d;%d", coords.X, coords.Y, coords.Z);

    // TODO : Actually generate chunks
    // This just fills stuff randomly so we have something to display

    std::mt19937 rnd(shift32(coords.X, 24) | shift32(coords.Y, 16) | shift32(coords.Z, 8) | m_Seed);
    std::uniform_real_distribution<> dis(0, 1);

    Chunk *chunk = new Chunk();

    // Probability of rocks
    float prob = powf(0.5f, 1.0f + fabsf((float)coords.Z));
    if(coords.Z < 0)
        prob = 1.0f - prob;

    for(int x = 0; x < CHUNK_SIZE; ++x)
        for(int y = 0; y < CHUNK_SIZE; ++y)
            for(int z = 0; z < CHUNK_DEPTH; z++)
                (*chunk)(x, y, z) = (dis(rnd) < prob)?Tile::ROCK:Tile::AIR;

    return std::shared_ptr<Chunk>(chunk);
}
