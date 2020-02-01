#pragma once
#include <vector>
class Snow
{
public:

	struct SnowFlake
	{
		float x;
		float y;
		float z;
		RenderObject* object;
	};

	Snow(int particleLimit, Renderer* renderer);
	void Update();

private:
	std::vector<SnowFlake> particles;
	int particleLimit;
	Renderer* renderer;

	void moveSnowFlake(float x, float y, float z, SnowFlake s);
	void displaceSnowFlake(float dx, float dy, float dz, SnowFlake s);
	SnowFlake makeSnowFlake(float x, float y, float z);
};

