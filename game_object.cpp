#include "game_object.h"
using namespace std;

GameObject::GameObject(string filepath, glm::vec3 size, glm::vec3 position, glm::vec3 velocity, vector<Rotation> rotations)
{
    this->model = new Model(filepath);
    this->size = size;
    this->position = position;
    this->velocity = velocity;
    this->rotations = rotations;
}

void GameObject::Draw(Shader shader)
{
    glm::mat4 model = glm::mat4(1);
    model = glm::translate(model, position);
    model = glm::scale(model, size);
    for (Rotation rotation : rotations)
	model = glm::rotate(model, glm::radians(rotation.angle), rotation.axis);
    shader.SetMatrix4("model", model);

    this->model->Draw(shader);
}