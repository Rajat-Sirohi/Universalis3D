#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "game.h"
#include "resource_manager.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

const unsigned int SCR_WIDTH = 1600;
const unsigned int SCR_HEIGHT = 900;

Game Universalis(SCR_WIDTH, SCR_HEIGHT);

int main(int argc, char *argv[])
{
    srand(time(NULL));
    
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, false);
    
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Universalis", nullptr, nullptr);
    if (window == NULL)
	{
	    std::cout << "Failed to create GLFW window" << std::endl;
	    glfwTerminate();
	    return -1;
	}
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback); 
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
	    std::cout << "Failed to initialize GLAD" << std::endl;
	    return -1;
	}
    
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // wireframe
    
    Universalis.Init();
    
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    
    while (!glfwWindowShouldClose(window))
	{
	    float currentFrame = glfwGetTime();
	    deltaTime = currentFrame - lastFrame;
	    lastFrame = currentFrame;
	    glfwPollEvents();
	    
	    Universalis.ProcessInput(deltaTime);
	    
	    Universalis.Update(deltaTime);
	    
	    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	    Universalis.Render();
	    
	    glfwSwapBuffers(window);
	}
    
    ResourceManager::Clear();
    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (key >= 0 && key < 1024)
	{
	    if (action == GLFW_PRESS)
		Universalis.Keys[key] = true;
	    else if (action == GLFW_RELEASE)
		Universalis.Keys[key] = false;
	}
    if (action == GLFW_PRESS)
	Universalis.ProcessKeyPress(key);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    Universalis.Mouse_Position = glm::vec2(xpos, ypos);
    Universalis.ProcessMouseMovement();
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    Universalis.ProcessMouseScroll(xoffset, yoffset);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) 
	Universalis.ProcessMouseClick();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}