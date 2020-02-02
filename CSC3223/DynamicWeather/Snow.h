#pragma once
#include <vector>
#include "Particle.h";
#include "Renderer.h";

using namespace std;
class Snow
{
	public:
		Snow(Renderer* renderer);
		void Update();
	private:
		vector<Particle>* particles;
		Renderer* renderer;
};

