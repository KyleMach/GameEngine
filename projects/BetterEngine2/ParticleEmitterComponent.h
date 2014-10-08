/* Garrett Hogan */

#pragma once

#ifndef _PARTICLE_EMITTER_COMPONENT_H_
#define _PARTICLE_EMITTER_COMPONENT_H_

#include "Component.h"
#include "GameObject.h"
#include "Shader.h"
#include <glm/glm.hpp>

struct Particle
{
	glm::vec3 position;
	glm::vec3 velocity;

	float lifetime;
	float lifespan;

	Particle() : lifetime(0), lifespan(0)
	{}
};

class ParticleEmitterComponent : public Component
{
public:

	ParticleEmitterComponent(GameObject *g);

	~ParticleEmitterComponent();

	Particle *m_particles;

	unsigned int m_maxParticles;

	glm::vec3  m_position;

	float m_lifespanMin;
	float m_lifespanMax;
};

#endif