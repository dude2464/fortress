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
            const value_type hx(std::hash<int>()(vec.x));
            const value_type hy(std::hash<int>()(vec.y));
            const value_type hz(std::hash<int>()(vec.z));
            return (hx << 2) ^ (hy << 1) ^ hz;
        }
    };
}

#endif
