#version 460 core

in vec4 v_Color;
in vec2 v_TextureCoordinates;
in float v_TextureIndex;

out vec4 color;

uniform sampler2D u_Textures[16];

void main()
{
    int index = int(v_TextureIndex);
    color = texture(u_Textures[index], v_TextureCoordinates) * v_Color;
}