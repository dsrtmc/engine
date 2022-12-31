#version 460 core

in vec2 TexCoord;

out vec4 color;

uniform sampler2D myTexture;
uniform bool u_UseTexture;
uniform vec3 u_Color;

void main()
{
    if (u_UseTexture)
    {
        color = texture(myTexture, TexCoord) * vec4(u_Color, 1.0f);
    }
    else
    {
        color = vec4(u_Color, 1.0f);
    }
}