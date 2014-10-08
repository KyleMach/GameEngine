/* Garrett Hogan */
#pragma once

#ifndef _RENDER_SYSTEM_H_
#define _RENDER_SYSTEM_H_

#include "System.h"
#include "GameObject.h"
#include <list>

struct OGL_FBXRenderData
{
	unsigned int VBO;
	unsigned int VAO;
	unsigned int IBO;
};

class RenderSystem : public System
{
public:
	// list of GameObjects
	//std::list<GameObject*> gameObjects;

	//RenderSystem *GetInstance();

	void Init(std::list<GameObject*> a_objList);
		// for each gameObject in the list
		// check which ones have an FBXComponent
		// intialize them them

	void RenderFBX(std::list<GameObject*> a_objList, glm::mat4 a_view, glm::mat4 a_projection, glm::mat4 a_camPos);
		// for each gameObject in the list
		// check which ones have an FBXComponent
		// make sure it has a shader
		// render them
	
	void Update(std::list<GameObject*> a_objList);
		// for each gameObject in the list
		// check which ones have an FBXComponent
		// update them

	void DestroyFBX(std::list<GameObject*> a_objList);
		// for each gameObject in the list
		// check which ones have an FBXComponent
		// destroy them

	void LoadShader(std::list<GameObject*> a_objList);

	void LoadTexture(std::list<GameObject*> a_objList);
};

#endif