#ifndef CORE_GENERATOR_H
#define CORE_GENERATOR_H

#include <memory>

#include "common/World.h"

class Chunk;

/**
 * World generator.
 *
 * This generates a world according to a fixed random seed. You can request new
 * chunks from it.
 */
class Generator {

private:
    unsigned long m_Seed;

public:
    Generator(unsigned long seed);
    std::shared_ptr<Chunk> generate(const ChunkCoordinates &coords);

};

#endif
