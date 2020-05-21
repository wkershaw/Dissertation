#include "Weather.h"

Weather::Weather(Vector3 position, Vector3 scale, Renderer* renderer)
{
	this->position = position;
	this->scale = scale;
	this->renderer = renderer;
}
