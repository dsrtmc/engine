#version 460 core
layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec4 a_Color;

uniform mat4 u_Transform;
uniform mat4 u_VP;

out vec4 v_Color;

void main()
{
    v_Color = a_Color;
    gl_Position = u_VP * u_Transform * vec4(a_Pos, 1.0);
}