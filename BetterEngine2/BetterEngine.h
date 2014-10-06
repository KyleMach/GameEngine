#pragma once

#include "Application.h"
#include "GameObject.h"
#include "RenderSystem.h"
#include <list>
#include <glm/glm.hpp>

// derived application class that wraps up all globals neatly
class BetterEngine : public Application
{
public:

	BetterEngine();
	virtual ~BetterEngine();

protected:

	virtual bool onCreate(int a_argc, char* a_argv[]);
	virtual void onUpdate(float a_deltaTime);
	virtual void onDraw();
	virtual void onDestroy();

	void CreateObject(const char *a_fbxFilePath, const char *a_texFilePath, const char *a_vShaderSource, const char *a_fShaderSource);

	RenderSystem *rs = new RenderSystem();

	glm::mat4	m_cameraMatrix;
	glm::mat4	m_projectionMatrix;

	std::list<GameObject*> gameObjects;
};

/*
	GameObject:

		pointer to components

//////////////////////////////////////////////////

	RenderSystem:

		list of objects to render

		InitFBXComponents
			- take in a list of GameObjects
			- make sure they have fbx components
			- initialize them

		RenderFBXComponents
			- take in a list of GameObjects
			- make sure they have fbx components
			- render them

		UpdateFBXComponents
			- take in a list of GameObjects
			- make sure they have fbx components
			- update them

		DestroyFBXComponents
			- take in a list of GameObjects
			- make sure they have fbx components
			- destroy them

////////////////////////////////////////////////

	FBXComponent:

		--pointer to FBXFile
		--pointer to Shader

		--textures

////////////////////////////////////////////////

	Shader:
		
		--list of uniforms
		--shader handle

		AddUniform:
			- takes in a uniform type and a name 
			  to associate with a uniform handle

		LoadShader:
			- loads shader handle

////////////////////////////////////////////////

	Uniform:

		--uniform type
		--uniform handle
		--uniform name

////////////////////////////////////////////////

	U_TYPES:

		--e3fv
		--e4fv
		--emat4
		--e1i

////////////////////////////////////////////////

	T_NAMES:
		
		--DiffuseTexture
		--AmbientTexture
		--GlowTexture
		--SpecularTexture
		--GlossTexture
		--NormalTexture
		--AlphaTexture
		--DisplacementTexture

////////////////////////////////////////////////

	Factory:

		CreateObject:
			
			- intialize object
			- register it with render system
			- return it

*/