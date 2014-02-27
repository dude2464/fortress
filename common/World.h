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
class Chunk {

protected:
    Tile m_Tiles[CHUNK_SIZE * CHUNK_SIZE];

public:
    inline Tile operator()(int x, int y) const
    {
        return m_Tiles[y * CHUNK_SIZE + x];
    }

};

class World {

public:
    virtual const std::shared_ptr<Chunk> getChunk(int X, int Y) = 0;

};

#endif
