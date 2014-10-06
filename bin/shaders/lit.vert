#version 330
in vec4 Position;
in vec4 Normal;
in vec2 TexCoord1;

out vec3 position;
out vec3 vNormal;
out vec2 vTexCoord1;

uniform mat4 view;
uniform mat4 projection;


void main()
{	
	position = Position.xyz;
	vTexCoord1 = TexCoord1;
	vNormal = Normal.xyz;
	gl_Position = projection * view * Position;
}