#pragma once

#include "Enemy.h"

class Octopus : public Enemy {

public:
	static void CreateDivePaths();

	void Hit(PhysEntity* other) override;

	Octopus(int path, int index, bool challenge, bool diver);
	~Octopus();

private:
	static std::vector<std::vector<Vector2>> sDivePaths;

	bool mDiver;
	bool mWasHit;

	void FlyInComplete() override;
	Vector2 LocalFormationPosition() override;

	void HandleDiveState() override;

	void RenderDiveState() override;
};