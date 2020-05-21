#pragma once
#include "Renderer.h"
#include "../../Common/Vector3.h"
#include "../../Common/Vector4.h"
#include "../../Common/Vector2.h"

using namespace NCL;
using namespace CSC3223;

class Draw {
public:
	Draw(Renderer* renderer) { this->renderer = renderer; };
	RenderObject* DrawPlane(Vector3 position, Vector2 scale, Vector4 colour);
	RenderObject* DrawPatchedPlane(Vector3 position, Vector2 scale, Vector4 colour);
	RenderObject* DrawCuboid(Vector3 position, Vector3 scale, Vector4 colour);

private:
	Renderer* renderer;

};
