/* Garrett Hogan */
#pragma once

#ifndef _SHADER_H_
#define _SHADER_H_

#include "GameObject.h"
#include <list>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>
#include <stb_image.h>

enum U_TYPES { e3fv, e4fv, emat4, e1f };

const char T_NAMES[8][64] =
{
	"DiffuseTexture",
	"AmbientTexture",
	"GlowTexture",
	"SpecularTexture",
	"GlossTexture",
	"NormalTexture",
	"AlphaTexture",
	"DisplacementTexture"
};

struct Uniform
{
	unsigned int m_handle;
	U_TYPES m_type;
	GLchar* m_name;
};

class Shader
{
public:

	const char *m_vSource;
	const char *m_fSource;

	std::list<Uniform*> m_uniforms;
	GameObject *pOwner;
	unsigned int m_shaderHandle;

	Shader(GameObject *g) : pOwner(g)
	{}

	void AddUniform(GLchar *a_name, U_TYPES a_type);
	void LoadShader();
};


#endif