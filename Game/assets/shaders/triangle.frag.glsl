#version 460 core

in vec2 TexCoord;
in vec4 v_Color;

out vec4 color;

void main()
{
    color = vec4(0.5 - (v_Color * vec4(1.0f)).rgb, 1.0);
}