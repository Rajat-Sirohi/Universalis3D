#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

#include "shader.h"
#include "texture.h"
#include "mesh.h"

struct Rotation {
    float angle;
    glm::vec3 axis;
};

class GameObject
{
public:
    Mesh *mesh;
    Texture2D texture;
    glm::vec3 position, velocity;
    std::vector<Rotation> rotations;

    GameObject(Texture2D, glm::vec3 position = glm::vec3(0), glm::vec3 velocity = glm::vec3(0), std::vector<Rotation> rotations = {});
    void Draw(Shader shader);

private:
    Mesh *generateMesh();
};

#endif