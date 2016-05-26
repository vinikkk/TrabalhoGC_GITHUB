#version 330 core
in vec2 TexCoord;

out vec4 color;

uniform sampler2D diffuse;

void main()
{
    color = texture(diffuse, TexCoord);
	//color = vec4(1.0f);
}