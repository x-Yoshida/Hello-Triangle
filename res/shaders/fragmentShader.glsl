#version 330 core

uniform vec4 triangleColor;
layout(location = 0) out vec4 color;

void main()
{
    color = vec4(triangleColor);
}