#include "game_object.h"
#include "resource_manager.h"

GameObject::GameObject(Texture2D texture, glm::vec3 position, glm::vec3 velocity, std::vector<Rotation> rotations)
{
    this->texture = texture;
    this->position = position;
    this->velocity = velocity;
    this->rotations = rotations;
    
    mesh = generateMesh();
    mesh->setupRenderData();
}

void GameObject::Draw(Shader shader)
{
    glm::mat4 model = glm::mat4(1);
    model = glm::translate(model, position);
    for (Rotation rotation : rotations)
	model = glm::rotate(model, glm::radians(rotation.angle), rotation.axis);
    shader.SetMatrix4("model", model);

    mesh->Draw(shader);
}

Mesh *GameObject::generateMesh()
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    
    Vertex v1 = { glm::vec3(-0.5, -0.5, 0),  glm::vec2(1, 1) };
    Vertex v2 = { glm::vec3(0.5, -0.5, 0),   glm::vec2(0, 1) };
    Vertex v3 = { glm::vec3(-0.5, 0.5, 0),   glm::vec2(1, 0) };
    Vertex v4 = { glm::vec3(0.5, 0.5, 0),    glm::vec2(0, 0) };
    vertices.push_back(v1);
    vertices.push_back(v2);
    vertices.push_back(v3);
    vertices.push_back(v4);
    
    indices = {
	0, 1, 2,
	1, 2, 3
    };
    
    return new Mesh(vertices, indices, texture);
}