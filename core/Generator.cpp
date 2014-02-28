#include <cmath>
#include <random>

#include "core/Generator.h"
#include "core/World.h"

Generator::Generator(unsigned long seed)
  : m_Seed(seed)
{
}

static int shift32(uint32_t x, uint32_t y)
{
    return (x << y | x >> (32-y)) & 0xFFFFFFFF;
}

std::shared_ptr<Chunk> Generator::generate(int X, int Y, int Z)
{
    // TODO : Actually generate chunks
    // This just fills stuff randomly so we have something to display

    std::mt19937 rnd(shift32(X, 24) | shift32(Y, 16) | shift32(Z, 8) | m_Seed);
    std::uniform_real_distribution<> dis(0, 1);

    Chunk *chunk = new Chunk();

    // Probability of rocks
    float prob = powf(0.5f, 1.0f + fabsf((float)Z));
    if(Z < 0)
        prob = 1.0f - prob;

    for(int x = 0; x < CHUNK_SIZE; ++x)
        for(int y = 0; y < CHUNK_SIZE; ++y)
            for(int z = 0; z < CHUNK_DEPTH; z++)
                (*chunk)(x, y, z) = (dis(rnd) < prob)?Tile::ROCK:Tile::AIR;

    return std::shared_ptr<Chunk>(chunk);
}
