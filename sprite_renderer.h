#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.h"
#include "texture.h"

class SpriteRenderer
{
public:
    SpriteRenderer(Shader shader);
    ~SpriteRenderer();
    void DrawSprite(Texture2D texture, glm::vec3 position, glm::vec3 size, float rotate, glm::vec3 color);
private:
    Shader shader; 
    unsigned int quadVAO;
    void initRenderData();
};

#endif