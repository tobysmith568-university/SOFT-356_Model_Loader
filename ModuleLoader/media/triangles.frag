#version 450 core

out vec4 fColor;
in vec4 fragColour;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
	fColor = texture(ourTexture, TexCoord);
}
