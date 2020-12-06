#include "sprite_renderer.h"

SpriteRenderer::SpriteRenderer(Shader shader)
{
    this->shader = shader;
    this->initRenderData();
}

SpriteRenderer::~SpriteRenderer()
{
    glDeleteVertexArrays(1, &this->quadVAO);
}

void SpriteRenderer::DrawSprite(Texture2D texture, glm::vec3 position, glm::vec3 size, float rotate, glm::vec3 color)
{
    this->shader.Use();
    
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::scale(model, size);
    //model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f)); 
    
    this->shader.SetMatrix4("model", model);
    this->shader.SetVector3f("spriteColor", color);
    
    glActiveTexture(GL_TEXTURE0);
    texture.Bind();
    
    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void SpriteRenderer::initRenderData()
{
    unsigned int VBO;
    float vertices[] = { 
	// pos                 // tex
        0.5f,   0.5f,  0.0f,   1.0f, 0.0f,
        0.5f,  -0.5f,  0.0f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.0f,   0.0f, 0.0f,
	
        0.5f,  -0.5f,  0.0f,   1.0f, 1.0f,
        -0.5f, -0.5f,  0.0f,   0.0f, 1.0f, 
        -0.5f,  0.5f,  0.0f,   0.0f, 0.0f
    };
    
    glGenVertexArrays(1, &this->quadVAO);
    glGenBuffers(1, &VBO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glBindVertexArray(this->quadVAO);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}