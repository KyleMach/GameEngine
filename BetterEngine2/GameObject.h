/* Garrett Hogan */
#pragma once

#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include "FBXComponent.h"
#include "DirLight.h"

class GameObject
{
public:

	FBXComponent *m_FBXComponent;
	DirLight * m_DirLight;


	GameObject() : m_FBXComponent(nullptr),
				   m_DirLight(nullptr) {}

	~GameObject(){}

};

#endif