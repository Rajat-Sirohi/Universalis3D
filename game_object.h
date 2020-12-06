#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "texture.h"
#include "sprite_renderer.h"

class GameObject
{
public:
    glm::vec3   Position, Size, Velocity;
    glm::vec3   Color;
    float       Rotation;
    Texture2D   Sprite;	
    GameObject();
    GameObject(glm::vec3 pos, glm::vec3 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec3 velocity = glm::vec3(0.0f));
    virtual void Draw(SpriteRenderer &renderer);
};

#endif