#ifndef MODEL_H
#define MODEL_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include <string>

#include "mesh.h"
#include "shader.h"
#include "texture.h"

class Model
{
public:
    std::vector<Mesh *> meshes;
    std::string directory;
    Model(std::string path);
    void Draw(Shader shader);
    
private:
    
    void loadModel(std::string path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh *processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
};

#endif