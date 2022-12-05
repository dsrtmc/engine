#version 330 core

in vec2 TexCoord;

out vec4 color;

uniform sampler2D myTexture;
uniform bool u_useTexture;

void main()
{
    if (u_useTexture)
    {
        color = texture(myTexture, TexCoord);
    }
    else
    {
        color = vec4(0.2f, 0.3f, 0.4f, 1.0f);
    }
}