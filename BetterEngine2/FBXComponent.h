/* Garrett Hogan */
#pragma once

#ifndef _FBX_COMPONENT_H_
#define _FBX_COMPONENT_H_

#include "Component.h"
#include <FBXFile.h>

class Shader;

class FBXComponent : public Component
{
public:

	FBXFile *m_pFBXFile;
	Shader *m_pShader;

	FBXComponent(GameObject *pOwner) : Component(pOwner),
		m_pFBXFile(nullptr), m_pShader(nullptr)
	{}

	const char *m_texPath;

	unsigned int m_texture1;
	unsigned int m_texture2;
};

#endif