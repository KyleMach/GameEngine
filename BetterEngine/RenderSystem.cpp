#include "RenderSystem.h"
#include "GameObject.h"
#include "Utilities.h"
#include "Shader.h"
#include <stb_image.h>
#include <glm/ext.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <FBXFile.h>
#include <list>
#include <cstring>

void RenderSystem::LoadTexture(std::list<GameObject*> a_objList)
{
	int height, width, format;

	for each(GameObject* g in a_objList)
	{
		if (g && g->m_FBXComponent)
		{
			unsigned char* pixelData = stbi_load(g->m_FBXComponent->m_texPath, &width, &height, &format, STBI_default);

			glGenTextures(1, &g->m_FBXComponent->m_texture1);
			glBindTexture(GL_TEXTURE_2D, g->m_FBXComponent->m_texture1);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixelData);
			glBindTexture(GL_TEXTURE_2D, 0);

			delete[]pixelData;
		}
	}
}

void RenderSystem::Init(std::list<GameObject*> a_objList)
{
	LoadTexture(a_objList);

	for each(GameObject *g in a_objList)
	{
		if (g && g->m_FBXComponent)
		{

			// get mesh and material count
			unsigned int meshCount = g->m_FBXComponent->m_pFBXFile->getMeshCount();
			unsigned int matCount = g->m_FBXComponent->m_pFBXFile->getMaterialCount();

			for (int i = 0; i < meshCount; ++i)
			{
				// get current mesh
				FBXMeshNode *pMesh = g->m_FBXComponent->m_pFBXFile->getMeshByIndex(i);

				// generate render data for VBO, IBO, VAO
				// assign it to m_userData so it can be retrieved in render function
				OGL_FBXRenderData *ro = new OGL_FBXRenderData();
				pMesh->m_userData = ro;

				// generate VBO, IBO, VAO
				glGenBuffers(1, &ro->VBO);
				glGenBuffers(1, &ro->IBO);
				glGenVertexArrays(1, &ro->VAO);

				// bind buffers and array
				glBindVertexArray(ro->VAO);
				glBindBuffer(GL_ARRAY_BUFFER, ro->VBO);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ro->IBO);

				// send vert data to vbo
				glBufferData(GL_ARRAY_BUFFER, pMesh->m_vertices.size() * sizeof(FBXVertex), pMesh->m_vertices.data(), GL_STATIC_DRAW);

				// send vert data to ibo
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, pMesh->m_indices.size() * sizeof(unsigned int), pMesh->m_indices.data(), GL_STATIC_DRAW);

				unsigned int v_index = 0;

				// checks which properties the vertex contains
				// enables the proper ones
				if (pMesh->m_vertexAttributes & FBXVertex::ePOSITION)
				{
					glEnableVertexAttribArray(v_index);
					glVertexAttribPointer(v_index, 4, GL_FLOAT, GL_FALSE, sizeof(FBXVertex), (char*)FBXVertex::PositionOffset);
					v_index++;
				}

				if (pMesh->m_vertexAttributes & FBXVertex::eCOLOUR)
				{
					glEnableVertexAttribArray(v_index);
					glVertexAttribPointer(v_index, 4, GL_FLOAT, GL_FALSE, sizeof(FBXVertex), (char*)FBXVertex::ColourOffset);
					v_index++;
				}

				if (pMesh->m_vertexAttributes & FBXVertex::eNORMAL)
				{
					glEnableVertexAttribArray(v_index);
					glVertexAttribPointer(v_index, 4, GL_FLOAT, GL_FALSE, sizeof(FBXVertex), (char*)FBXVertex::NormalOffset);
					v_index++;
				}

				if (pMesh->m_vertexAttributes & FBXVertex::eTANGENT)
				{
					glEnableVertexAttribArray(v_index);
					glVertexAttribPointer(v_index, 4, GL_FLOAT, GL_FALSE, sizeof(FBXVertex), (char*)FBXVertex::TangentOffset);
					v_index++;
				}

				if (pMesh->m_vertexAttributes & FBXVertex::eBINORMAL)
				{
					glEnableVertexAttribArray(v_index);
					glVertexAttribPointer(v_index, 4, GL_FLOAT, GL_FALSE, sizeof(FBXVertex), (char*)FBXVertex::BiNormalOffset);
					v_index++;
				}

				if (pMesh->m_vertexAttributes & FBXVertex::eINDICES)
				{
					glEnableVertexAttribArray(v_index);
					glVertexAttribPointer(v_index, 4, GL_FLOAT, GL_FALSE, sizeof(FBXVertex), (char*)FBXVertex::IndicesOffset);
					v_index++;
				}

				if (pMesh->m_vertexAttributes & FBXVertex::eWEIGHTS)
				{
					glEnableVertexAttribArray(v_index);
					glVertexAttribPointer(v_index, 4, GL_FLOAT, GL_FALSE, sizeof(FBXVertex), (char*)FBXVertex::WeightsOffset);
					v_index++;
				}

				if (pMesh->m_vertexAttributes & FBXVertex::eTEXCOORD1)
				{
					glEnableVertexAttribArray(v_index);
					glVertexAttribPointer(v_index, 4, GL_FLOAT, GL_FALSE, sizeof(FBXVertex), (char*)FBXVertex::TexCoord1Offset);
					v_index++;
				}

				/*if (pMesh->m_vertexAttributes & FBXVertex::eTEXCOORD2)
				{
					glEnableVertexAttribArray(v_index);
					glVertexAttribPointer(v_index, 4, GL_FLOAT, GL_FALSE, sizeof(FBXVertex), (char*)FBXVertex::TexCoord2Offset);
					v_index++;
				}*/

				glBindVertexArray(0);
				glBindBuffer(GL_ARRAY_BUFFER, 0);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			}
		}
	}
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void RenderSystem::RenderFBX(std::list<GameObject*> a_objList, glm::mat4 a_view, glm::mat4 a_projection, glm::mat4 a_camPos)
{
	/*
		loops through each GameOBject in the list
		checks if it has an FBXComponent attached
		if so, loop through each uniform in the shader
		attached to the FBXComponent and set its handle
		to the proper location
	*/
	for each(GameObject *g in a_objList)
	{
		/*for (int i = 0; i < 10; ++i)
		{

			char a[] = "  Test";
			a[0] = i+'0';
			unsigned loc = 0;
			
			glGetUniformLocation(g->m_FBXComponent->m_pShader->m_shaderHandle, a);

			int blue = -3;
		}*/





		if (g && g->m_FBXComponent && g->m_FBXComponent->m_pShader)
		{

			glUseProgram(g->m_FBXComponent->m_pShader->m_shaderHandle);

			//glGetUniformLocation(shader,"");
			for each(Uniform *uni in g->m_FBXComponent->m_pShader->m_uniforms)
			{
				uni->m_handle = glGetUniformLocation(g->m_FBXComponent->m_pShader->m_shaderHandle, uni->m_name);
			}

			for (int i = 0; i < g->m_FBXComponent->m_pFBXFile->getMeshCount(); ++i)
			{
				FBXMeshNode *pMesh = g->m_FBXComponent->m_pFBXFile->getMeshByIndex(i);

				OGL_FBXRenderData *ro = (OGL_FBXRenderData*)pMesh->m_userData;

				unsigned int uHandles[FBXMaterial::TextureTypes::TextureTypes_Count];

				// store each texture name in a handle
				for (int i = 0; i < FBXMaterial::TextureTypes::TextureTypes_Count; ++i)
				{
					uHandles[i] = glGetUniformLocation(g->m_FBXComponent->m_pShader->m_shaderHandle, T_NAMES[i]);
				}

				// activate each handle
				for (int i = 0; i < FBXMaterial::TextureTypes::TextureTypes_Count; ++i)
				{
					if (pMesh->m_material->textures[i])
					{
						glActiveTexture(GL_TEXTURE1 + i);
						glBindTexture(GL_TEXTURE_2D, pMesh->m_material->textures[i]->handle);
						glUniform1i(uHandles[i], i + 1);
					}
				}

				glActiveTexture(GL_TEXTURE0);

				for each(Uniform *uni in g->m_FBXComponent->m_pShader->m_uniforms)
				{
					switch (uni->m_type)
					{
					case e4fv:
						/*
						this case consists of mostly light color info
						- light color
						- ambient light color

						would go here
					*/
						if (strcmp(uni->m_name, "DirLightPos") == 0)
						{
							glUniform4fv(uni->m_handle, 1, glm::value_ptr(g->m_DirLight->m_DirLightPos));
						}
						break;

					case e3fv:

						// position info goes here

						break;

					case emat4:

						if (strcmp(uni->m_name, "Model") == 0)
						{
							glUniformMatrix4fv(uni->m_handle, 1, false, glm::value_ptr(pMesh->m_globalTransform));
						}
						if (strcmp(uni->m_name, "View") == 0)
							glUniformMatrix4fv(uni->m_handle, 1, false, glm::value_ptr(a_view));

						if (strcmp(uni->m_name, "Projection") == 0)
							glUniformMatrix4fv(uni->m_handle, 1, false, glm::value_ptr(a_projection));

						break;
					case e1f:
						/* the floats go here */

						break;
					default:
						printf("Error, you suck.");
						break;
					}
				}

				glBindVertexArray(ro->VAO);
				glDrawElements(GL_TRIANGLES, pMesh->m_indices.size(), GL_UNSIGNED_INT, 0);
			}

			glUseProgram(0);
		}
	}

}

void RenderSystem::Update(std::list<GameObject*> a_objList)
{
	for each(GameObject *g in a_objList)
	{
		if (g && g->m_FBXComponent)
		{
			g->m_FBXComponent->m_pFBXFile->getRoot()->updateGlobalTransform();
		}
	}
}

void RenderSystem::DestroyFBX(std::list<GameObject*> a_objList)
{
	for each(GameObject *g in a_objList)
	{
		if (g && g->m_FBXComponent)
		{
			unsigned int meshCount = g->m_FBXComponent->m_pFBXFile->getMeshCount();
			unsigned int matCount = g->m_FBXComponent->m_pFBXFile->getMaterialCount();

			for (int i = 0; i < meshCount; ++i)
			{
				FBXMeshNode *pMesh = g->m_FBXComponent->m_pFBXFile->getMeshByIndex(i);
				OGL_FBXRenderData *ro = (OGL_FBXRenderData*)pMesh->m_userData;

				// delete buffers
				glDeleteBuffers(1, &ro->VBO);
				glDeleteBuffers(1, &ro->VAO);
				glDeleteVertexArrays(1, &ro->VAO);

				delete ro;
			}

			for (int i = 0; i < matCount; ++i)
			{
				FBXMaterial *pMat = g->m_FBXComponent->m_pFBXFile->getMaterialByIndex(i);
				
				for (int j = 0; j < FBXMaterial::TextureTypes_Count; ++j)
				{
					// delete texture if it was loaded
					if (pMat->textures[j] != 0)
					{
						glDeleteTextures(1, &pMat->textures[j]->handle);
					}
				}
			}
		}
	}
}

/*RenderSystem *RenderSystem::GetInstance()
{
	RenderSystem instance;

	return &instance;
}*/