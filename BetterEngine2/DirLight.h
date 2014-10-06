/*   Kyle Mach  */
#pragma once

#include "Component.h"
#include <glm/ext.hpp>

#ifndef _DIRLIGHT_H_
#define _DIRLIGHT_H_

class GameObject;

class DirLight : public Component
{
private:

public:
	
	Shader *m_shader;

	DirLight(GameObject *DirLight) : Component(DirLight) { }
	~DirLight() { }
	
	glm::vec4 m_DirLightColor; 
	glm::vec4 m_DirLightPos;
	glm::vec4 m_DirLightDir;
	float m_DirLightInt;
};
#endif