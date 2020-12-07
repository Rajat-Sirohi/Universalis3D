#version 330 core

out vec4 color;

uniform vec3 terrainColor;

void main()
{
   color = vec4(terrainColor, 1.0f);
}