#include "terrain.h"

Terrain::Terrain(int size, int width, int depth, glm::vec3 color) : Size(size), Width(width), Depth(depth), Color(color)
{
    generateMesh();
}

void Terrain::generateMesh()
{
    for (int z = 0; z < Depth; z++) {
	for (int x = 0; x < Width; x++) {
	    vertices.push_back((float)x / ((float)Width - 1) * Size);
	    float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	    vertices.push_back(r*1.0f);
	    vertices.push_back((float)z / ((float)Depth - 1) * Size);
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