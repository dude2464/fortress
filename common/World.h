#ifndef COMMON_WORLD_H
#define COMMON_WORLD_H

#include <list>
#include <memory>

#include "common/Vector.h"

#define CHUNK_SIZE_E 7
#define CHUNK_SIZE (1 << CHUNK_SIZE_E) // 128
#define CHUNK_DEPTH_E 2
#define CHUNK_DEPTH (1 << CHUNK_DEPTH_E) // 4

class Coordinates;

/**
 * Identifies a chunk in the world.
 *
 * This can be converted into Coordinates, in which case it'll represent the
 * position of this chunk's top-left corner.
 */
typedef CoordinatesMultiple<CHUNK_SIZE, CHUNK_SIZE,
                            CHUNK_DEPTH,
                            Coordinates> ChunkCoordinates;

/**
 * This represents a tile in the world.
 *
 * You can get the ChunkCoordinates of the chunk it's on using chunk().
 */
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

namespace std {
    template<>
    struct hash<Coordinates> {
        typedef Coordinates argument_type;
        typedef std::size_t value_type;

        value_type operator()(const argument_type &vec) const
        {
            return std::hash<Vector3>()(vec);
        }
    };
}

enum class Tile : unsigned char {
    ROCK    = 0x01,
    AIR     = 0x02
};

enum class Designation : unsigned char {
    BUILD   = 0x01,
    DIG     = 0x02
};

/**
 * A chunk is a small portion of the world.
 */
template<class T>
class BaseChunk {

protected:
    T m_Tiles[CHUNK_SIZE * CHUNK_SIZE * CHUNK_DEPTH];

public:
    inline T operator()(int x, int y, int z) const
    {
        x = mod(x, CHUNK_SIZE);
        y = mod(y, CHUNK_SIZE);
        z = mod(z, CHUNK_DEPTH);
        return m_Tiles[(z * CHUNK_DEPTH + y) * CHUNK_SIZE + x];
    }

    inline T operator()(const Coordinates &coords) const
    {
        return (*this)(coords.x, coords.y, coords.z);
    }

    inline T &operator()(int x, int y, int z)
    {
        return m_Tiles[(z * CHUNK_DEPTH + y) * CHUNK_SIZE + x];
    }

    inline T &operator()(const Coordinates &coords)
    {
        return (*this)(coords.x, coords.y, coords.z);
    }

};

class IEntity {

public:
    enum {
        T_ANIMAL    = 0x07,
        T_HUMANOID  = 0x03,
        DWARF       = 0x01
    };

protected:
    Coordinates m_Position;

public:
    IEntity(Coordinates position)
        : m_Position(position)
    {
    }
    virtual ~IEntity();

    inline Coordinates position() const
    {
        return m_Position;
    }

    virtual unsigned int type() const = 0;
    virtual std::string name() const = 0;

};

/**
 * Ground layer, contains stuff.
 */
class IChunk : public BaseChunk<Tile> {

public:
    virtual std::list<std::shared_ptr<const IEntity> > entities() = 0;

};

/**
 * Order layer, contains what we asked.
 */
typedef BaseChunk<Designation> IDesignationChunk;

/**
 * The world.
 */
class IWorld {

public:
    inline  std::shared_ptr<const IChunk> getChunk(int X, int Y, int Z)
    {
        return getChunk(ChunkCoordinates(X, Y, Z));
    }
    virtual std::shared_ptr<const IChunk> getChunk(
            const ChunkCoordinates &chunk) = 0;

    inline std::shared_ptr<IDesignationChunk> getDesignationChunk(
            int X, int Y, int Z)
    {
        return getDesignationChunk(ChunkCoordinates(X, Y, Z));
    }
    virtual std::shared_ptr<IDesignationChunk> getDesignationChunk(
            const ChunkCoordinates &chunk) = 0;

};

#endif
