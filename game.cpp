#include "game.h"
#include "resource_manager.h"
#include "sprite_renderer.h"
#include "game_object.h"
#include "camera.h"

SpriteRenderer *Renderer;
GameObject *Player;
Camera *Cam;
float lastX, lastY;
bool firstMouse = true;

Game::Game(unsigned int width, unsigned int height) 
    : Keys(), Width(width), Height(height)
{
    
}

Game::~Game()
{
    delete Renderer;
    delete Player;
    delete Cam;
}

void Game::Init()
{
    ResourceManager::LoadShader("shaders/sprite.vert", "shaders/sprite.frag", "sprite");
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)this->Width / (float)this->Height, 0.1f, 100.0f);
    ResourceManager::GetShader("sprite").Use();
    ResourceManager::GetShader("sprite").SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
    
    Player = new GameObject(glm::vec3(0.0f), glm::vec3(1.0f),
			    ResourceManager::LoadTexture("textures/buddy.jpg", true, "buddy"));
    
    Cam = new Camera(glm::vec3(0.0f, 0.0f, 3.0f),
		     glm::vec3(0.0f, 1.0f, 0.0f));
    lastX = this->Width / 2.0f;
    lastY = this->Height / 2.0f;
}

void Game::Update(float dt)
{
    glm::mat4 projection = glm::perspective(glm::radians(Cam->Zoom), (float)this->Width / (float)this->Height, 0.1f, 100.0f);
    glm::mat4 view = Cam->GetViewMatrix();
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    ResourceManager::GetShader("sprite").SetMatrix4("view", view);
}

void Game::ProcessInput(float dt)
{
    if (this->Keys[GLFW_KEY_W])
	Cam->ProcessKeyboard(FORWARD, dt);
    if (this->Keys[GLFW_KEY_S])
	Cam->ProcessKeyboard(BACKWARD, dt);
    if (this->Keys[GLFW_KEY_A])
	Cam->ProcessKeyboard(LEFT, dt);
    if (this->Keys[GLFW_KEY_D])
	Cam->ProcessKeyboard(RIGHT, dt);
}

void Game::ProcessKeyPress(int key)
{
    if (key == GLFW_KEY_SPACE);
}

void Game::ProcessMouseMovement()
{
    double xpos = Mouse_Position.x;
    double ypos = Mouse_Position.y;
    
    if (firstMouse) {
	lastX = xpos;
	lastY = ypos;
	firstMouse = false;
    }
    
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    
    lastX = xpos;
    lastY = ypos;
    
    Cam->ProcessMouseMovement(xoffset, yoffset);
}

void Game::ProcessMouseScroll(double xoffset, double yoffset)
{
    Cam->ProcessMouseScroll(yoffset);
}

void Game::ProcessMouseClick()
{

}

void Game::Render()
{
    Player->Draw(*Renderer);
}