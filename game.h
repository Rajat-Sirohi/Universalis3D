#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <map>
#include <set>

class Game
{
public:
    bool Keys[1024];
    glm::vec2 Mouse_Position;
    unsigned int Width, Height;
    Game(unsigned int width, unsigned int height);
    ~Game();
    void Init();
    void ProcessInput(float dt);
    void ProcessKeyPress(int key);
    void ProcessMouseMovement();
    void ProcessMouseScroll(double xoffset, double yoffset);
    void ProcessMouseClick();
    void Update(float dt);
    void Render();
};

#endif