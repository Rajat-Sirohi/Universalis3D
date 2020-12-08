#include "game.h"
#include "resource_manager.h"
#include "game_object.h"
#include "terrain.h"
#include "camera.h"

GameObject *Player;

Terrain *Terr;
int terrSize = 100;

Camera *Cam;
float lastX, lastY;
bool firstMouse = true;

Game::Game(unsigned int width, unsigned int height) 
    : Keys(), Width(width), Height(height)
{
    
}

Game::~Game()
{
    delete Terr;
    delete Cam;
}

void Game::Init()
{
    ResourceManager::LoadShader("shaders/generic.vert", "shaders/generic.frag", "generic");
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)this->Width / this->Height, 0.1f, 100.0f);
    ResourceManager::GetShader("generic").Use();
    ResourceManager::GetShader("generic").SetInteger("image", 0);
    ResourceManager::GetShader("generic").SetMatrix4("projection", projection);
    
    Player = new GameObject(ResourceManager::LoadTexture("textures/buddy.jpg", true, "player"),
			    glm::vec3(terrSize/2.0, 2, terrSize/2.0));

    Terr = new Terrain(terrSize, ResourceManager::LoadTexture("textures/rocks.jpg", true, "terrain"));
    
    Cam = new Camera(glm::vec3(0), glm::vec3(0,1,0));
    lastX = this->Width / 2.0f;
    lastY = this->Height / 2.0f;
}

void Game::Update(float dt)
{
    Player->velocity.y -= 3 * dt;
    Player->position += Player->velocity * dt;

    if (Player->position.y < 0.5) {
	Player->position.y = 0.5;
	Player->velocity.y *= -0.7;
    }

    Player->rotations.clear();
    Rotation vertical = { Cam->Pitch, Cam->Right };
    Rotation horizontal = { Cam->Yaw, glm::vec3(0,1,0) };
    Player->rotations.push_back(vertical);
    Player->rotations.push_back(horizontal);
    
    Cam->Position = Player->position - 5.0f * Cam->Front;

    glm::mat4 projection = glm::perspective(glm::radians(Cam->Zoom), (float)this->Width / (float)this->Height, 0.1f, 100.0f);
    glm::mat4 view = Cam->GetViewMatrix();
    ResourceManager::GetShader("generic").SetMatrix4("projection", projection);
    ResourceManager::GetShader("generic").SetMatrix4("view", view);
}

void Game::ProcessInput(float dt)
{
    float thrust = 10.0f;
    
    if (Keys[GLFW_KEY_LEFT_SHIFT])
	Player->velocity *= 0.95;
    if (Keys[GLFW_KEY_SPACE])
	Player->velocity.y += thrust * dt;

    if (Keys[GLFW_KEY_W])
	Player->velocity += Cam->Front * thrust * dt;
    if (Keys[GLFW_KEY_S])
	Player->velocity -= Cam->Front * thrust * dt;
    if (Keys[GLFW_KEY_A])
	Player->velocity -= Cam->Right * thrust * dt;
    if (Keys[GLFW_KEY_D])
	Player->velocity += Cam->Right * thrust * dt;
}

void Game::ProcessKeyPress(int key)
{
    
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
    
    float xoffset = lastX - xpos;
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
    Player->Draw(ResourceManager::GetShader("generic"));
    Terr->Draw(ResourceManager::GetShader("generic"));
}