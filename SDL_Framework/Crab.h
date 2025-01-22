#pragma once
#include "Enemy.h"


class Crab : public Enemy {

public:

	void Hit(PhysEntity* other) override;

	Crab(int index, bool challenge);
	~Crab();

private:
	static std::vector<std::vector<Vector2>> sDivePaths;

	bool mEscort;

	Vector2 LocalFormationPosition() override;

};