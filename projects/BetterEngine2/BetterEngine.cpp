#include "BetterEngine.h"
#include "Gizmos.h"
#include "Utilities.h"
#include "FBXComponent.h"
#include "Shader.h"
#include "GameObject.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>

#define DEFAULT_SCREENWIDTH 1280
#define DEFAULT_SCREENHEIGHT 720

BetterEngine::BetterEngine()
{

}

BetterEngine::~BetterEngine()
{

}

void BetterEngine::CreateObject(const char *a_fbxFilePath, const char *a_texFilePath)
{
	GameObject *g;
	g = new GameObject();

	g->m_FBXComponent = new FBXComponent(g);
	g->m_FBXComponent->m_texPath = a_texFilePath;
	g->m_FBXComponent->m_pFBXFile = new FBXFile();
	g->m_FBXComponent->m_pFBXFile->load(a_fbxFilePath, FBXFile::UNITS_CENTIMETER);
	g->m_FBXComponent->m_pFBXFile->initialiseOpenGLTextures();

	g->m_FBXComponent->m_pShader = new Shader(g);

	// instead of passing in shader source as parameters 
	// just hard code them in for each shader like this
	g->m_FBXComponent->m_pShader->m_vSource = "../bin/shaders/TestShader.vert";
	g->m_FBXComponent->m_pShader->m_fSource = "../bin/shaders/TestShader.frag";
	//////////////////////////////////////////////////////////////////////////
	g->m_FBXComponent->m_pShader->AddUniform("View", emat4);
	g->m_FBXComponent->m_pShader->AddUniform("Projection", emat4);
	g->m_FBXComponent->m_pShader->AddUniform("Model", emat4);
	
	gameObjects.push_back(g);
}

bool BetterEngine::onCreate(int a_argc, char* a_argv[]) 
{
	// initialise the Gizmos helper class
	Gizmos::create();

	// create a world-space matrix for a camera
	m_cameraMatrix = glm::inverse( glm::lookAt(glm::vec3(10,10,10),glm::vec3(0,0,0), glm::vec3(0,1,0)) );

	// get window dimensions to calculate aspect ratio
	int width = 0, height = 0;
	glfwGetWindowSize(m_window, &width, &height);

	// create a perspective projection matrix with a 90 degree field-of-view and widescreen aspect ratio
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, width / (float)height, 0.1f, 1000.0f);

	// set the clear colour and enable depth testing and backface culling
	glClearColor(0.25f,0.25f,0.25f,1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);


	CreateObject("../bin/models/models_misc/soulspear/soulspear.fbx", "../bin/textures/crate.png");
	//CreateObject
	rs->Init(gameObjects);

	return true;
}

void BetterEngine::onUpdate(float a_deltaTime) 
{
	// update our camera matrix using the keyboard/mouse
	Utility::freeMovement( m_cameraMatrix, a_deltaTime, 10 );

	// clear all gizmos from last frame
	Gizmos::clear();
	
	// add an identity matrix gizmo
	Gizmos::addTransform( glm::mat4(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1) );

	// add a 20x20 grid on the XZ-plane
	for ( int i = 0 ; i < 21 ; ++i )
	{
		Gizmos::addLine( glm::vec3(-10 + i, 0, 10), glm::vec3(-10 + i, 0, -10), 
						 i == 10 ? glm::vec4(1,1,1,1) : glm::vec4(0,0,0,1) );
		
		Gizmos::addLine( glm::vec3(10, 0, -10 + i), glm::vec3(-10, 0, -10 + i), 
						 i == 10 ? glm::vec4(1,1,1,1) : glm::vec4(0,0,0,1) );
	}

	// quit our application when escape is pressed
	if (glfwGetKey(m_window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
		quit();

	rs->Update(gameObjects);
}

void BetterEngine::onDraw() 
{
	// clear the backbuffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// get the view matrix from the world-space camera matrix
	glm::mat4 viewMatrix = glm::inverse( m_cameraMatrix );
	
	// draw the gizmos from this frame
	Gizmos::draw(m_projectionMatrix, viewMatrix);

	rs->RenderFBX(gameObjects, viewMatrix, m_projectionMatrix, m_cameraMatrix);

	// get window dimensions for 2D orthographic projection
	int width = 0, height = 0;
	glfwGetWindowSize(m_window, &width, &height);
	Gizmos::draw2D(glm::ortho<float>(0, width, 0, height, -1.0f, 1.0f));
}

void BetterEngine::onDestroy()
{
	// clean up anything we created

	rs->DestroyFBX(gameObjects);

	Gizmos::destroy();
}

// main that controls the creation/destruction of an application
int main(int argc, char* argv[])
{
	// explicitly control the creation of our application
	Application* app = new BetterEngine();
	
	if (app->create("AIE - BetterEngine",DEFAULT_SCREENWIDTH,DEFAULT_SCREENHEIGHT,argc,argv) == true)
		app->run();
		
	// explicitly control the destruction of our application
	delete app;

	return 0;
}