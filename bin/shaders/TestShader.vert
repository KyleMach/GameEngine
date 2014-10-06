#version 330

in vec4 Position;
in vec4 Normal;
in vec4 Tangent;
in vec4 BiNormal;
in vec2 TexCoord1;

uniform mat4 View;
uniform mat4 Projection;
uniform mat4 Model;

void main()
{
	gl_Position = Projection * View * Model * Position;
}