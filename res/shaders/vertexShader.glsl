#version 330 core

layout(location = 0) in vec4 verticesPositions;
layout(location = 1) in vec4 color;

smooth out vec4 triangleColor;

void main()
{
    gl_Position = verticesPositions;
    triangleColor = color;
}