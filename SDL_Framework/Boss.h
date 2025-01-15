#pragma once
#include "Enemy.h"
#include "CaptureBeam.h"
#include "Random.h"
#include "Texture.h"
//#include "RedShip.h"

namespace SDL_Framework {

	class Boss : public Enemy {
	public:
		static void CreateDivePaths();

		void Dive(int type = 0) override;
		void Hit(PhysEntity* other) override;

		Boss(int path, int index, bool challenge);
		~Boss();

	private:
		static std::vector<std::vector<Vector2>> sDivePaths;

		bool mCaptureDive;
		bool mCapturing;
		bool mCapturedPlayer;
		int mCurrentPath;

		bool mWasHit;

		Vector2 LocalFormationPosition() override;

		bool mIsCaptured;
		CaptureBeam* mCaptureBeam;
		//RedShip* mRedShip;

		void HandleCaptureBeam();

		void HandleDiveState() override;

		void RenderDiveState() override;
	};
}