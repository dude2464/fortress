#ifndef COMMON_VECTOR_H
#define COMMON_VECTOR_H

class Vector3 {

public:
    int x, y, z;

public:
    Vector3(int x_, int y_, int z_)
      : x(x_), y(y_), z(z_)
    {
    }

    inline bool operator==(const Vector3 &other) const
    {
        return (x == other.x &&
                y == other.y &&
                z == other.z);
    }

    inline bool operator!=(const Vector3 &other) const
    {
        return !(*this == other);
    }

};

#endif
