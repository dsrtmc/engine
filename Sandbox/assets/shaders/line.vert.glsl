#version 460 core
layout (location = 0) in vec3 a_Pos;

uniform mat4 u_Transform;
uniform mat4 u_VP;

void main()
{
    gl_Position = u_VP * u_Transform * vec4(a_Pos, 1.0);
}