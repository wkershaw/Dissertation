#include "Snow.h"

Snow::Snow(Renderer* renderer)
{
	particles = new vector<Particle>();
	this->renderer = renderer;
}

void Snow::Update()
{
	if (particles->size() < 1000) {
		int toAdd = rand() % 5;
		for (int i = 0; i < toAdd; i++) {
			float x = (((rand() % 100)) / 5.0) - 10;
			float z = (((rand() % 100) / 5.0) - 50);
			particles->push_back(Particle(x, 10, z));
			renderer->AddRenderObject(particles->back().getObject());
		}
	}
	for (int i = 0; i < particles->size(); i++) {
		if (particles->at(i).getPosition().y < -30) {
			float x = (((rand() % 100)) / 5.0 - 10);
			float z = (((rand() % 100) / 5.0) - 50);
			particles->at(i).MoveTo(x, 10, z);
		}
		else {
			particles->at(i).DisplaceBy(0, -0.1f, 0);
		}

	}
}
