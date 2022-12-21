#version 460 core

in vec2 TexCoord;
in vec4 v_Color;

out vec4 color;

uniform vec4 u_Color;
uniform sampler2D Texture;

void main()
{
    color = texture(Texture, TexCoord) * v_Color;
}