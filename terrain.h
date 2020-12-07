#ifndef TERRAIN_H
#define TERRAIN_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

#include "texture.h"

class Terrain
{
public:
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    int Size, Width, Depth; // Size of gaps, # of vertices in x-dim, # of vertices in z-dim
    Texture2D Texture;
    glm::vec3 Position;
    Terrain(int size, int width, int depth, Texture2D texture, glm::vec3 position = glm::vec3(0.0f));

private:
    void generateMesh();
};

#endif