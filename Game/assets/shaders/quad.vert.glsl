#version 460 core
layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec4 a_Color;
layout (location = 2) in vec2 a_TextureCoordinates;
layout (location = 3) in float a_TextureIndex;

out vec4 v_Color;
out vec2 v_TextureCoordinates;
out float v_TextureIndex;

uniform mat4 u_Transform;
uniform mat4 u_VP;

void main()
{
    v_Color = a_Color;
    v_TextureCoordinates = a_TextureCoordinates;
    v_TextureIndex = a_TextureIndex;
    gl_Position = u_VP * u_Transform * vec4(a_Position, 1.0);
}