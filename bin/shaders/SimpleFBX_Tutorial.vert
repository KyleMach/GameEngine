#version 330

in vec4 Position;
in vec4 Normal;
/*in vec4 Tangent;
in vec4 BiNormal;
in vec2 TexCoord1;

out vec2 vTexCoord1;
out vec3 vNormal;
out vec3 vLightDir;

uniform mat4 MVP;
uniform mat4 MV;
uniform mat4 NormalMatrix;

uniform vec3 LightPosition;
*/
void main()
{

	/*vec3 eye_normal = (NormalMatrix * Normal).xyz;
	vec3 eye_tangent = (NormalMatrix * Tangent).xyz;
	vec3 eye_binormal = (NormalMatrix * BiNormal).xyz;
	
	vec3 eye_position = (MV * Position).xyz;
	vec3 eye_lightPos = (MV * vec4(LightPosition, 1)).xyz;
	
	vec3 lightDir = normalize(eye_lightPos - eye_position);
	
	vLightDir = lightDir;
	vLightDir.x = dot(lightDir, eye_tangent);
	vLightDir.y = dot(lightDir, eye_binormal);
	vLightDir.z = dot(lightDir, eye_normal);
	
	vNormal = eye_normal;
	
	vTexCoord1 = TexCoord1;
	*/
	gl_Position = vec3(0,0,0);
	
	//gl_Position = Projection * View * Model * Position;
}