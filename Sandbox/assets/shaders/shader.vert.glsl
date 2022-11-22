#version 330 core
layout (location = 0) in vec3 a_Pos;

void main()
{
    gl_Position = a_Pos;
}