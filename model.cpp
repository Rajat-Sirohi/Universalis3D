#include <iostream>

#include "model.h"
#include "resource_manager.h"
using namespace std;

Model::Model(string path)
{
    loadModel(path);
}

void Model::Draw(Shader shader)
{
    for (Mesh *mesh : meshes)
	mesh->Draw(shader);
}

void Model::loadModel(string path)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
	cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
	return;
    }
    directory = path.substr(0, path.find_last_of('/'));

    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene)
{
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }

    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}  

Mesh *Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;
    
    // process vertices
    for(unsigned int i = 0; i < mesh->mNumVertices; i++) {
	Vertex vertex;
	
	vertex.Position.x = mesh->mVertices[i].x;
	vertex.Position.y = mesh->mVertices[i].y;
	vertex.Position.z = mesh->mVertices[i].z;
	
	if(mesh->mTextureCoords[0]) {
	    vertex.TexCoords.x = mesh->mTextureCoords[0][i].x;
	    vertex.TexCoords.y = mesh->mTextureCoords[0][i].y;
	}
	else
	    vertex.TexCoords = glm::vec2(0.0f, 0.0f);
	
	vertices.push_back(vertex);
    }
    
    // process indices
    for(unsigned int i = 0; i < mesh->mNumFaces; i++) {
	aiFace face = mesh->mFaces[i];
	for(unsigned int j = 0; j < face.mNumIndices; j++)
	    indices.push_back(face.mIndices[j]);
    }
    
    // process material
    if(mesh->mMaterialIndex) {
	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
	
        vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    }
    
    return new Mesh(vertices, indices, textures);
}

vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName)
{
    vector<Texture> textures;
    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
	aiString file;
	mat->GetTexture(type, i, &file);
	string path = this->directory + '/' + file.C_Str();
	Texture texture = ResourceManager::LoadTexture(path.c_str(), true, typeName + std::to_string(i));
	textures.push_back(texture);
    }
    return textures;
}