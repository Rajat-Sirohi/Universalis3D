#ifndef TERRAIN_H
#define TERRAIN_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

#include "shader.h"
#include "texture.h"
#include "mesh.h"

class Terrain
{
public:
    Mesh *mesh;
    int size;
    Texture2D texture;
    glm::vec3 position;
    Terrain(int size, Texture2D texture, glm::vec3 position = glm::vec3(0.0f));
    void Draw(Shader shader);

private:
    Mesh *generateMesh();
};

#endif