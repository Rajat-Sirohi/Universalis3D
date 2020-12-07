#include "terrain.h"

Terrain::Terrain(int size, int width, int depth, Texture2D texture, glm::vec3 position) : Size(size), Width(width), Depth(depth), Texture(texture), Position(position)
{
    generateMesh();
}

void Terrain::generateMesh()
{
    for (int z = 0; z < Depth; z++) {
	for (int x = 0; x < Width; x++) {
	    // Position (uniformly distributed from 0 to Width by 0 to Depth)
	    float vx = (float)x / (Width - 1) * Size;
	    float vy = (float)rand() / RAND_MAX;
	    float vz = (float)z / (Depth - 1) * Size;
	    vertices.push_back(vx);
	    vertices.push_back(vy*0.0f);
	    vertices.push_back(vz);

	    // Texture Coords (uniformly distributed from 0 to 1)
	    float tx = (float)(vx*(Size-1) / Width) - 1;
	    float tz = (float)(vz*(Size-1) / Depth) - 1;
	    vertices.push_back(1.0 - tx);
	    vertices.push_back(1.0 - tz);
	}
    }
    int pointer = 0;
    for(int z = 0; z < Depth - 1; z++) {
	for(int x = 0; x < Width - 1; x++) {
	    int topLeft = (z*Width) + x;
	    int topRight = topLeft + 1;
	    int bottomLeft = ((z+1) * Width) + x;
	    int bottomRight = bottomLeft + 1;
	    indices.push_back(topLeft);
	    indices.push_back(bottomLeft);
	    indices.push_back(topRight);
	    indices.push_back(topRight);
	    indices.push_back(bottomLeft);
	    indices.push_back(bottomRight);
	}
    }
}