#include "resource_manager.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include <SOIL/SOIL.h>

std::map<std::string, Shader> ResourceManager::Shaders;
std::map<std::string, Texture> ResourceManager::Textures;

Shader ResourceManager::LoadShader(const char *vShaderFile, const char *fShaderFile, std::string name)
{
    Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile);
    return Shaders[name];
}

Shader ResourceManager::GetShader(std::string name)
{
    return Shaders[name];
}

Texture ResourceManager::LoadTexture(const GLchar *file, GLboolean alpha, std::string name)
{
    if (Textures.count(name) == 0)
	Textures[name] = loadTextureFromFile(file, alpha);
    return Textures[name];
}

Texture ResourceManager::GetTexture(std::string name)
{
    return Textures[name];
}

void ResourceManager::Clear()
{
    for (auto iter : Shaders)
        glDeleteProgram(iter.second.ID);
    for (auto iter : Textures)
        glDeleteTextures(1, &iter.second.ID);
}

Shader ResourceManager::loadShaderFromFile(const char *vShaderFile, const char *fShaderFile)
{
    std::string vertexCode;
    std::string fragmentCode;
    try
	{
	    std::ifstream vertexShaderFile(vShaderFile);
	    std::ifstream fragmentShaderFile(fShaderFile);
	    std::stringstream vShaderStream, fShaderStream;
	    
	    vShaderStream << vertexShaderFile.rdbuf();
	    fShaderStream << fragmentShaderFile.rdbuf();
	    
	    vertexShaderFile.close();
	    fragmentShaderFile.close();
	    
	    vertexCode = vShaderStream.str();
	    fragmentCode = fShaderStream.str();
	}
    catch (std::exception e)
	{
	    std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
	}
    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();
    
    Shader shader;
    shader.Compile(vShaderCode, fShaderCode);
    return shader;
}

Texture ResourceManager::loadTextureFromFile(const GLchar *file, GLboolean alpha)
{
    Texture texture;
    if (alpha)
	{
	    texture.Internal_Format = GL_RGBA;
	    texture.Image_Format = GL_RGBA;
	}
    
    int width, height;
    unsigned char* image = SOIL_load_image(file, &width, &height, 0, texture.Image_Format == GL_RGBA ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);
    texture.Generate(width, height, image);
    SOIL_free_image_data(image);
    
    return texture;
}