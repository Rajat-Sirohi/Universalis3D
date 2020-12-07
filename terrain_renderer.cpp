#include "terrain_renderer.h"

TerrainRenderer::TerrainRenderer(Shader shader)
{
    this->shader = shader;
}

TerrainRenderer::~TerrainRenderer()
{
    glDeleteVertexArrays(1, &this->VAO);
}

void TerrainRenderer::DrawTerrain(Terrain *terr)
{
    this->shader.Use();
    
    glm::mat4 model = glm::mat4(1.0f);
    
    this->shader.SetMatrix4("model", model);
    this->shader.SetVector3f("terrainColor", terr->Color);
    
    glBindVertexArray(this->VAO);
    glDrawElements(GL_TRIANGLES, terr->indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void TerrainRenderer::setupRenderData(Terrain *terr)
{
    unsigned int VBO, EBO;
    
    std::vector<float> vertices = terr->vertices;
    std::vector<unsigned int> indices = terr->indices;
    
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(this->VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}