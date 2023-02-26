#version 330 core
layout(location = 0) in vec4 verticesPositions;

void main()
{
    gl_Position = verticesPositions;
}