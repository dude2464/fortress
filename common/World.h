#ifndef COMMON_WORLD_H
#define COMMON_WORLD_H

#include <memory>

#include "common/Vector.h"

#define CHUNK_SIZE_E 7
#define CHUNK_SIZE (1 << CHUNK_SIZE_E) // 128
#define CHUNK_DEPTH_E 2
#define CHUNK_DEPTH (1 << CHUNK_DEPTH_E) // 4

class Coordinates;

typedef CoordinatesMultiple<CHUNK_SIZE, CHUNK_SIZE,
                            CHUNK_DEPTH,
                            Coordinates> ChunkCoordinates;

class Coordinates : public Vector3 {

public:
    Coordinates(int x_, int y_, int z_)
      : Vector3(x_, y_, z_)
    {
    }

    inline ChunkCoordinates chunk() const
    {
        return ChunkCoordinates(x >> CHUNK_SIZE_E,
                                y >> CHUNK_SIZE_E,
                                z >> CHUNK_DEPTH_E);
    }

};

enum class Tile : unsigned char {
    ROCK    = 0x01,
    AIR     = 0x02
};

/**
 * A chunk is a small portion of the world.
 */
class IChunk {

protected:
    Tile m_Tiles[CHUNK_SIZE * CHUNK_SIZE * CHUNK_DEPTH];

public:
    inline Tile operator()(int x, int y, int z) const
    {
        x = mod(x, CHUNK_SIZE);
        y = mod(y, CHUNK_SIZE);
        z = mod(z, CHUNK_DEPTH);
        return m_Tiles[(z * CHUNK_DEPTH + y) * CHUNK_SIZE + x];
    }

    inline Tile operator()(const Coordinates &coords) const
    {
        return (*this)(coords.x, coords.y, coords.z);
    }

};

/**
 * The world.
 */
class IWorld {

public:
    inline  std::shared_ptr<IChunk> getChunk(int X, int Y, int Z)
    {
        return getChunk(ChunkCoordinates(X, Y, Z));
    }

    virtual std::shared_ptr<IChunk> getChunk(const ChunkCoordinates &chunk) = 0;

};

#endif
