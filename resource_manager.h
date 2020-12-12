#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>

#include <glad/glad.h>

#include "shader.h"
#include "texture.h"

class ResourceManager
{
public:
    static std::map<std::string, Shader> Shaders;
    static std::map<std::string, Texture> Textures;
    static Shader LoadShader(const char *vShaderFile, const char *fShaderFile, std::string name);
    static Shader GetShader(std::string name);
    static Texture LoadTexture(const GLchar *file, GLboolean alpha, std::string name);
    static Texture GetTexture(std::string name);
    static void Clear();
private:
    ResourceManager() { }
    static Shader loadShaderFromFile(const char *vShaderFile, const char *fShaderFile);
    static Texture loadTextureFromFile(const GLchar *file, GLboolean alpha);
};

#endif