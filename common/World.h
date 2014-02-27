#ifndef COMMON_WORLD_H
#define COMMON_WORLD_H

#include <memory>

enum Tile {
    ROCK,
    AIR
};

#define CHUNK_SIZE 1024

/**
 * A chunk is a small square area.
 */
class IChunk {

protected:
    Tile m_Tiles[CHUNK_SIZE * CHUNK_SIZE];

public:
    inline Tile operator()(int x, int y) const
    {
        return m_Tiles[y * CHUNK_SIZE + x];
    }

};

/**
 * The world.
 */
class IWorld {

public:
    virtual const std::shared_ptr<IChunk> getChunk(int X, int Y) = 0;

};

#endif
