#pragma once

#include "Enemy.h"

class Octopus : public Enemy {

public:

	void Hit(PhysEntity* other) override;

	Octopus(int index, bool challenge);
	~Octopus();

private:
	static std::vector<std::vector<Vector2>> sDivePaths;

	bool mDiver;
	bool mWasHit;

	Vector2 LocalFormationPosition() override;

};