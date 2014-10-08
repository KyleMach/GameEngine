/* Garrett Hogan */

#include "Shader.h"
#include <stb_image.h>
#include <Utilities.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>
#include <cstring>

void Shader::AddUniform(GLchar *a_name, U_TYPES a_type)
{
	Uniform *uni = new Uniform;

	uni->m_name = new char[strlen(a_name)+1];
	strcpy_s(uni->m_name, strlen(a_name)+1, a_name);
	
	uni->m_type = a_type;

	m_uniforms.push_back(uni);
}

void Shader::LoadShader()
{
	const char *Inputs[] = { "Position", "Color", "Normal", "Tangent", "BiNormal"
		"Indices", "Weights", "TexCoord1", "TexCoord2" };

	const char *Outputs[] = { "OutColor" };

	GLuint vShader = Utility::loadShader(m_vSource, GL_VERTEX_SHADER);
	GLuint fShader = Utility::loadShader(m_fSource, GL_FRAGMENT_SHADER);

	m_shaderHandle = Utility::createProgram(vShader, 0, 0, 0, fShader, 8, Inputs, 1, Outputs);

	glDeleteShader(vShader);
	glDeleteShader(fShader);
}
