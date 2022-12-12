#version 460 core

in vec2 TexCoord;
in vec4 v_Color;

out vec4 color;

void main()
{
    color = v_Color * vec4(0.8f, 0.1f, 0.6f, 1.0f);
}