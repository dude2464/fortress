#ifndef PERLIN_PERLIN_H
#define PERLIN_PERLIN_H

class PerlinNoise3D {

private:
    float m_BaseFrequency;
    float m_Persistence;
    unsigned int m_Octaves;

public:
    PerlinNoise3D(float base_freq, float persistence, unsigned int octaves);
    float sample(float x, float y, float z);
    static float interpolate(float v1, float v2, float v3, float v4,
                             float v5, float v6, float v7, float v8,
                             float x, float y, float z);
    float interpolatedNoise(float x, float y, float z);
    float noise(int x, int y, int z);

};

#endif
