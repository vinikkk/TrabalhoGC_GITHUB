#version 330

layout (location = 0) in vec3 Position;
layout (location = 1) in vec2 TexCoord;
layout (location = 2) in vec3 Normal;

out vec3 fragPos;
out vec2 texCoord;
out vec3 normal;

uniform mat4 transform;

void main()
{
	gl_Position = transform * vec4(Position, 1.0);
	fragPos = vec3(transform * vec4(Position, 1.0));
	texCoord = TexCoord;
	
	normal = (transform * vec4(Normal, 0.0)).xyz;
}