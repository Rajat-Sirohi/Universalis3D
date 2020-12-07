#ifndef TERRAIN_RENDERER_H
#define TERRAIN_RENDERER_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "shader.h"
#include "terrain.h"

class TerrainRenderer
{
public:
    TerrainRenderer(Shader shader);
    ~TerrainRenderer();
    void DrawTerrain(Terrain *terr);
    void setupRenderData(Terrain *terr);
private:
    Shader shader; 
    unsigned int VAO;
};

#endif