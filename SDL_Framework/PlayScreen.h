#pragma once
#include "BackgroundStar.h"
#include "PlaySideBar.h"

using namespace SDL_Framework;

class PlayScreen : public GameEntity {

public:
	PlayScreen();
	~PlayScreen();

	void Update() override;
	void Render() override;

private:
	Timer* mTimer;
	AudioManager* mAudio;

	BackgroundStars* mStars;
	PlaySideBar* mSideBar;
};