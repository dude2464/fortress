#ifndef COMMON_WORLD_H
#define COMMON_WORLD_H

#include <memory>

enum class Tile : unsigned char {
    ROCK    = 0x01,
    AIR     = 0x02
};

#define CHUNK_SIZE 256
#define CHUNK_DEPTH 16

/**
 * A chunk is a small portion of the world.
 */
class IChunk {

protected:
    Tile m_Tiles[CHUNK_SIZE * CHUNK_SIZE * CHUNK_DEPTH];

public:
    inline Tile operator()(int x, int y, int z) const
    {
        return m_Tiles[(z * CHUNK_DEPTH + y) * CHUNK_SIZE + x];
    }

};

/**
 * The world.
 */
class IWorld {

public:
    virtual const std::shared_ptr<IChunk> getChunk(int X, int Y, int Z) = 0;

};

#endif
