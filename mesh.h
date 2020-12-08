#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

#include "shader.h"
#include "texture.h"

struct Vertex {
    glm::vec3 Position;
    glm::vec2 TexCoords;
};

class Mesh
{
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    Texture2D texture;
    unsigned int VAO;
    
    Mesh() { }
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Texture2D texture);
    ~Mesh();
    void Draw(Shader shader);
    void setupRenderData();
};

#endif