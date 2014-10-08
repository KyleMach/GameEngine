/* Garrett Hogan */
#pragma once

#ifndef _COMPONENT_H_
#define _COMPONENT_H_

class GameObject;

class Component
{
private:

	GameObject *pOwner;

public:

	Component(GameObject *Owner) : pOwner(Owner) {}

	virtual ~Component(){}

};

#endif