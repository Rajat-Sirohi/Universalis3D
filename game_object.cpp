#include "game_object.h"

GameObject::GameObject() 
    : Position(0.0f), Size(1.0f), Velocity(0.0f), Color(1.0f), Rotation(0.0f), Sprite() { }

GameObject::GameObject(glm::vec3 pos, glm::vec3 size, Texture2D sprite, glm::vec3 color, glm::vec3 velocity) 
    : Position(pos), Size(size), Velocity(velocity), Color(color), Rotation(0.0f), Sprite(sprite) { }

void GameObject::Draw(SpriteRenderer &renderer)
{
    renderer.DrawSprite(this->Sprite, this->Position, this->Size, this->Rotation, this->Color);
}