#include "perlin/Perlin.h"

#include <cmath>
#include <random>

PerlinNoise3D::PerlinNoise3D(float base_freq,
                             float persistence, unsigned int octaves)
  : m_BaseFrequency(base_freq), m_Persistence(persistence), m_Octaves(octaves)
{
}

float linearInterpolation(float v1, float v2, float x)
{
    return v1*(1.0f-x) + v2*x;
}

float PerlinNoise3D::interpolate(float v1, float v2, float v3, float v4,
                                 float v5, float v6, float v7, float v8,
                                 float x, float y, float z)
{
    // Tri-linear interpolation
    return linearInterpolation(
            linearInterpolation(
                    linearInterpolation(v1, v2, x),
                    linearInterpolation(v4, v3, x),
                    y),
            linearInterpolation(
                    linearInterpolation(v5, v6, x),
                    linearInterpolation(v8, v7, x),
                    y),
            z);
}

float PerlinNoise3D::noise(int x, int y, int z)
{
    int n = x + y * 57 + z * 61;
    n = (n << 13) ^ n;
    return (1.0 - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7FFFFFFF)/1073741824.0f);
}

float PerlinNoise3D::interpolatedNoise(float x, float y, float z)
{
    int xi = int(x), yi = int(y), zi = int(z);
    float xf = x - xi, yf = y - yi, zf = z - zi;

    float v1 = noise(xi  , yi  , zi  );
    float v2 = noise(xi+1, yi  , zi  );
    float v3 = noise(xi+1, yi+1, zi  );
    float v4 = noise(xi  , yi+1, zi  );
    float v5 = noise(xi  , yi  , zi+1);
    float v6 = noise(xi+1, yi  , zi+1);
    float v7 = noise(xi+1, yi+1, zi+1);
    float v8 = noise(xi  , yi+1, zi+1);

    return interpolate(v1, v2, v3, v4, v5, v6, v7, v8, xf, yf, zf);
}

float PerlinNoise3D::sample(float x, float y, float z)
{
    float total = 0.0f;
    for(size_t i = 0; i < m_Octaves; ++i)
    {
        float frequency = powf(2.0f, i) * m_BaseFrequency;
        float amplitude = powf(m_Persistence, i);
        total += amplitude * interpolatedNoise(x * frequency,
                                               y * frequency,
                                               z * frequency);
    }
    return total;
}
