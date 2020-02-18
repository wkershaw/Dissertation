#pragma once
#include "Renderer.h"
#include "Particle.h"
#include <vector>
using namespace std;
using namespace NCL;
using namespace NCL::Rendering;
using namespace NCL::CSC3223;
class Snow
{
	public:
		Snow(Renderer* renderer, Vector3 position, Vector3 size, int maxParticles, int rate);
		void Update();


	private:

		void UpdateParticle(Particle& p);
		Vector3 generateRandomCoord();
		Vector3 generateRanomVelocity();
		vector<Particle>* particles;
		Renderer* renderer;
		OGLShader* snowflakeShader;
		OGLMesh* mesh;
		
		Vector3 position;
		Vector3 size;
		float resolution;
		int maxParticles;
		int rate;
		TextureBase* snowflakeTexture;
};

