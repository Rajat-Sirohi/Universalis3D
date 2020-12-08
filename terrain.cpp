#include "terrain.h"
#include "resource_manager.h"

Terrain::Terrain(int size, Texture2D texture, glm::vec3 position)
{
    this->size = size;
    this->texture = texture;
    this->position = position;
    
    mesh = generateMesh();
    mesh->setupRenderData();
}

void Terrain::Draw(Shader shader)
{
    glm::mat4 model = glm::mat4(1);
    model = glm::translate(model, position);
    shader.SetMatrix4("model", model);

    mesh->Draw(shader);
}

Mesh *Terrain::generateMesh()
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    
    int width = size, depth = size;
    for (int z = 0; z < depth; z++) {
	for (int x = 0; x < width; x++) {
	    // Position (uniformly distributed from 0 to width by 0 to depth)
	    float px = (float)x / (width - 1) * size;
	    float py = 0 * (float)rand() / RAND_MAX;
	    float pz = (float)z / (depth - 1) * size;

	    // Texture Coords (uniformly distributed from 0 to 1)
	    float tx = (float)(px*(size-1) / width) - 1;
	    float tz = (float)(pz*(size-1) / depth) - 1;
	    
	    Vertex v = {
		glm::vec3(px, py, pz),
		glm::vec2(1 - tx, 1 - tz)
	    };
	    vertices.push_back(v);
	}
    }
    int pointer = 0;
    for(int z = 0; z < depth - 1; z++) {
	for(int x = 0; x < width - 1; x++) {
	    int topLeft = (z*width) + x;
	    int topRight = topLeft + 1;
	    int bottomLeft = ((z+1) * width) + x;
	    int bottomRight = bottomLeft + 1;
	    indices.push_back(topLeft);
	    indices.push_back(bottomLeft);
	    indices.push_back(topRight);
	    indices.push_back(topRight);
	    indices.push_back(bottomLeft);
	    indices.push_back(bottomRight);
	}
    }
    
    return new Mesh(vertices, indices, texture);
}