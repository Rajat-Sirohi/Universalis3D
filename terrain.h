#ifndef TERRAIN_H
#define TERRAIN_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

class Terrain
{
public:
    int Size, Width, Depth;
    glm::vec3 Color;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    Terrain(int size, int width, int depth, glm::vec3 color);

private:
    void generateMesh();
};

#endif