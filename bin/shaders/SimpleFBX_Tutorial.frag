#version 330

/*in vec2 vTexCoord1;
in vec3 vNormal;
in vec3 vLightDir;

uniform sampler2D DiffuseTexture;
uniform sampler2D NormalTexture;
uniform sampler2D SpecularTexture;

uniform vec4 AmbientLightColor;
uniform vec4 LightColor;

float SpecularPower;
uniform int toggle;
*/
out vec4 outColor;

void main()
{
/*
	vec4 finalColor = vec4(0,0,0,0);
	
	SpecularPower = 0.1;
	
	vec3 normalColor = texture(NormalTexture, vTexCoord1).xyz;
	vec4 diffuseColor = texture(DiffuseTexture, vTexCoord1);
	vec4 specularColor = texture(SpecularTexture, vTexCoord1);

	vec3 N = normalize((2.0 * normalColor - 1.0) + vNormal);
	vec3 L = vLightDir;
	
	float diffuseIntensity = max(0.0, dot(N,L));
	
	vec4 ambientColor = diffuseColor * AmbientLightColor;
	
	finalColor.rgb = (diffuseIntensity * LightColor.rgb) * diffuseColor.rgb + ambientColor.rgb;
	
	vec3 reflection = normalize(reflect(-normalize(vLightDir), N));
	float spec = max(0.0, dot(reflection, N));
	float fSpec = pow(spec, 5.0);
	
	finalColor.rgb += vec3(fSpec, fSpec, fSpec) * specularColor.xyz;
	
	outColor = finalColor;
	outColor.a = 1;
	

	outColor = texture2D(DiffuseTexture, vUV.xy) * vColor;
	
	float decay = 0.0;
	
	//if( texture2D( DecayTexture, vUV.xy ).r < DecayValue )
		//decay = 1.0;
	
	//outColor.a = 0.5f;
	*/
	
	outColor = vec4(1,1,1,1);
}