#version 460 core

in vec2 TexCoord;

out vec4 color;

uniform vec4 u_Color;
uniform sampler2D Texture;

void main()
{
    color = texture(Texture, TexCoord) * u_Color;
}