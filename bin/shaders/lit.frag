#version 330

in vec3 vNormal;
in vec2 vTexCoord1;
in vec3 position;

out vec4 outColor;

uniform sampler2D DiffuseTexture;
uniform vec3 cameraPosition;
uniform vec3 Light;

void main()
{

	vec3 N = normalize(vNormal);
	vec3 L = normalize(position - Light);
	
	vec3 R = reflect(-L, N);
	vec3 E = normalize(cameraPosition - position);
	
	//Ambient Color
	vec3 Ambient = vec3(0.1, 0.1, 0.1);
	
	//Diffuse
	float d = max(0, dot(N, L));
	vec3 D = vec3(0,0,1);
	vec3 Diffuse = D * d;
	
	//Specular
	float s = pow(max(0, dot(E, R)), 128);
	vec3 S = vec3(1,0,0);
	vec3 Specular = S * s;
	
	outColor = vec4(Ambient + Diffuse + Specular, 1);
}