#pragma once
#include "RenderObject.h"
#include "../../Common/Vector3.h"
#include "../../Plugins/OpenGLRendering/OGLMesh.h"
#include "../../Plugins/OpenGLRendering/OGLShader.h"
#include "Renderer.h"
using namespace NCL;
using namespace NCL::Rendering;
using namespace NCL::CSC3223;
class Particle
{
public:
	Particle(Vector3 position,Vector3 velocity, OGLMesh* mesh, OGLShader* shader,TextureBase* texture, Renderer* renderer);
	void MoveTo(Vector3 newPosition);
	void DisplaceBy(Vector3 displacment);
	void Update();
	Vector3 getPosition();
	
private:
	Vector3 position;
	Vector3 velocity;
	RenderObject* object;
	OGLMesh* mesh;
	OGLShader* shader;
	Renderer* renderer;
};

