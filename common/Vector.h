#ifndef COMMON_VECTOR_H
#define COMMON_VECTOR_H

#include <algorithm>

#include "common/utils.h"

class Vector3 {

public:
    int x, y, z;

public:
    Vector3(int x_, int y_, int z_)
      : x(x_), y(y_), z(z_)
    {
    }

};

inline bool operator==(const Vector3 &a, const Vector3 &b)
{
    return (a.x == b.x && a.y == b.y && a.z == b.z);
}

inline bool operator!=(const Vector3 &a, const Vector3 &b)
{
    return !(a == b);
}

template<int XM, int YM, int ZM, typename VectorClass=Vector3>
class CoordinatesMultiple {

public:
    int X, Y, Z;

public:
    CoordinatesMultiple(int X_, int Y_, int Z_)
      : X(X_), Y(Y_), Z(Z_)
    {
    }

    operator VectorClass() const
    {
        return VectorClass(X * XM, Y * YM, Z * ZM);
    }

};

namespace std {
    template<>
    struct hash<Vector3> {
        typedef Vector3 argument_type;
        typedef std::size_t value_type;

        value_type operator()(const argument_type &vec) const
        {
            return std::hash<int>()(shift32(vec.x, 16) ^
                                    shift32(vec.y, 8) ^
                                    vec.z);
        }
    };

    template<int XM, int YM, int ZM, typename VectorClass>
    struct hash<CoordinatesMultiple<XM, YM, ZM, VectorClass> > {
        typedef CoordinatesMultiple<XM, YM, ZM, VectorClass> argument_type;
        typedef std::size_t value_type;

        value_type operator()(const argument_type &vec) const
        {
            return std::hash<int>()(shift32(vec.X, 16) ^
                                    shift32(vec.Y, 8) ^
                                    vec.Z);
        }
    };
}

template<typename V>
inline V vec_min(const V &a, const V &b)
{
    return V(std::min(a.x, b.x),
             std::min(a.y, b.y),
             std::min(a.z, b.z));
}

template<typename V>
inline V vec_max(const V &a, const V &b)
{
    return V(std::max(a.x, b.x),
             std::max(a.y, b.y),
             std::max(a.z, b.z));
}

#endif
