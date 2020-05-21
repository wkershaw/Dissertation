#pragma once
#include "Renderer.h"
#include "Particle.h"
#include "Weather.h"
#include <vector>
using namespace std;
using namespace NCL;
using namespace NCL::CSC3223;


class Snow : public Weather
{
public:
	Snow(Vector3 position, Vector3 scale, Renderer* renderer);
	void Update();
	int getParticleCount() { return snowflakes->size(); };

private:

	void UpdateSnowflake(Particle& p);
	Vector3 generateRandomCoord();
	Vector3 generateRanomVelocity();
	vector<Particle>* snowflakes;
	OGLShader* shader;
	OGLMesh* mesh;
	float resolution = 100.0f;
	TextureBase* texture;
};



