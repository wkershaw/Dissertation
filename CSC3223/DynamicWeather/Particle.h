#pragma once
#include "RenderObject.h"
using namespace NCL::CSC3223;
class Particle
{
public:
	Particle(float x, float y, float z);
	void MoveTo(float x, float y, float z);
	void DisplaceBy(float x, float y, float z);
	RenderObject* getObject();
	Vector3 getPosition();
private:
	float x;
	float y;
	float z;
	RenderObject* object;
};

