#pragma once
#include "Star.h"

class StarLayer {
public:
	StarLayer(int layer);
	~StarLayer();

	void Update();
	void Render();

private:
	static const int STAR_COUNT = 50;
	Star* mStars[STAR_COUNT];
};