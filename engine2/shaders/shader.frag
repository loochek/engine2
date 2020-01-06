#version 330 core

in vec2 TexCoord;
out vec4 color;

uniform sampler2D texture_diffuse;
uniform sampler2D texture_specular;

void main()
{
	color = texture(texture_diffuse, TexCoord);
}