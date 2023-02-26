#version 330 core

smooth in vec4 triangleColor;
layout(location = 0) out vec4 outColor;

void main()
{
    outColor = vec4(triangleColor);
}