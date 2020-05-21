#pragma once
#include "../../Common/Vector3.h"
#include "Renderer.h"

using namespace std;
using namespace NCL;
using namespace NCL::Maths;
using namespace NCL::CSC3223;
class Weather
{
	public:
		Weather(Vector3 position, Vector3 scale, Renderer* renderer);
		Vector3 GetPosition() { return position; };
		Vector3 GetScale() { return scale; };

	protected:
		Vector3 position;
		Vector3 scale;
		Renderer* renderer;

};

