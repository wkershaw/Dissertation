#pragma once
#include "Renderer.h"
#include "Particle.h"
#include "Weather.h"
#include <vector>

using namespace std;
using namespace NCL;
using namespace NCL::CSC3223;

class Cloud : public Weather
{
	public:
		Cloud(Vector3 position, Vector3 scale, Renderer* renderer);
		int getParticleCount() { return particles->size(); };

	private:
		TextureBase* texture0;
		TextureBase* texture1;
		TextureBase* texture2;
		vector<Particle>* particles;
		OGLShader* shader;
		OGLMesh* cloudPoint;
};

