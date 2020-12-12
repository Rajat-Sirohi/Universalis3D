#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>

#include "shader.h"
#include "model.h"

struct Rotation {
    float angle;
    glm::vec3 axis;
};

class GameObject
{
public:
    Model *model;
    glm::vec3 size, position, velocity;
    std::vector<Rotation> rotations;

    GameObject(std::string filepath, glm::vec3 size = glm::vec3(1), glm::vec3 position = glm::vec3(0), glm::vec3 velocity = glm::vec3(0), std::vector<Rotation> rotations = {});
    void Draw(Shader shader);
};

#endif