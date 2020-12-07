#include "game.h"
#include "resource_manager.h"
#include "terrain.h"
#include "terrain_renderer.h"
#include "camera.h"

TerrainRenderer *TerrRenderer;
Terrain *Terr;
float terrFactor = 20.0f;

Camera *Cam;
float camHeight = 1.0f;
float lastX, lastY;
bool firstMouse = true;

Game::Game(unsigned int width, unsigned int height) 
    : Keys(), Width(width), Height(height)
{
    
}

Game::~Game()
{
    delete TerrRenderer;
    delete Terr;
    delete Cam;
}

void Game::Init()
{
    ResourceManager::LoadShader("shaders/terrain.vert", "shaders/terrain.frag", "terrain");
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)this->Width / this->Height, 0.1f, 100.0f);
    ResourceManager::GetShader("terrain").Use();
    ResourceManager::GetShader("terrain").SetInteger("image", 0);
    ResourceManager::GetShader("terrain").SetMatrix4("projection", projection);
    TerrRenderer = new TerrainRenderer(ResourceManager::GetShader("terrain"));
    
    Terr = new Terrain(terrFactor, terrFactor, terrFactor,
		       ResourceManager::LoadTexture("textures/rocks.jpg", true, "ground"));
    TerrRenderer->setupRenderData(Terr);
    
    Cam = new Camera(glm::vec3(terrFactor/2.0, camHeight, terrFactor/2.0),
		     glm::vec3(0.0f, 1.0f, 0.0f), 90.0f);
    lastX = this->Width / 2.0f;
    lastY = this->Height / 2.0f;
}

void Game::Update(float dt)
{
    glm::mat4 projection = glm::perspective(glm::radians(Cam->Zoom), (float)this->Width / (float)this->Height, 0.1f, 100.0f);
    glm::mat4 view = Cam->GetViewMatrix();
    ResourceManager::GetShader("terrain").SetMatrix4("projection", projection);
    ResourceManager::GetShader("terrain").SetMatrix4("view", view);

    // Ground collision
    if (Cam->Position.y < camHeight)
	Cam->Position.y = camHeight;
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
    if (key == GLFW_KEY_LEFT_SHIFT)
	Cam->MovementSpeed *= 0.8f;
    if (key == GLFW_KEY_SPACE)
	Cam->MovementSpeed *= 1.2f;
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
    TerrRenderer->DrawTerrain(Terr);
}