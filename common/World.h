#ifndef COMMON_WORLD_H
#define COMMON_WORLD_H

#include <memory>

#include "common/Vector.h"

#define CHUNK_SIZE_E 7
#define CHUNK_SIZE (2 << (CHUNK_SIZE_E-1)) // 128
#define CHUNK_DEPTH_E 2
#define CHUNK_DEPTH (2 << (CHUNK_DEPTH_E-1)) // 4

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
