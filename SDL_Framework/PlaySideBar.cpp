#include "PlaySideBar.h"

PlaySideBar::PlaySideBar() {
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();

	mTopBackground = new GLTexture("Black.png");
	mTopBackground->Parent(this);
	mTopBackground->Scale(Vector2(8.5f, 1.0f));
	mTopBackground->Position(0.0f, 200.0f); 

	mBottomBackground = new GLTexture("Black.png");
	mBottomBackground->Parent(this);
	mBottomBackground->Scale(Vector2(8.5f, 1.0f));
	mBottomBackground->Position(-520.0f, 910.0f);

	mHighLabel = new GLTexture("HIGH SCORE", "emulogic.ttf", 12, { 0, 255, 0 });
	mHighLabel->Parent(this);
	mHighLabel->Position(-390.0f, 350.0f);

	mP1ScoreLabel = new GLTexture("SCORE<1>", "emulogic.ttf", 12, { 0, 255, 0 });
	mP1ScoreLabel->Parent(this);
	mP1ScoreLabel->Position(-580.0f, 350.0f);

	mP2ScoreLabel = new GLTexture("SCORE<2>", "emulogic.ttf", 12, { 0, 255, 0 });
	mP2ScoreLabel->Parent(this);
	mP2ScoreLabel->Position(-200.0f, 350.0f);

	mHighScoreBoard = new Scoreboard();
	mHighScoreBoard->Parent(this);
	mHighScoreBoard->Position(-343.0f, 380.0f);

	mOneUpLabel = new GLTexture("1UP", "emulogic.ttf", 20, { 0, 255, 0 });
	mOneUpLabel->Parent(this);
	mOneUpLabel->Position(-400.0f, 836.0f);

	mBlinkTimer = 0.0f;
	mBlinkInterval = 0.5f;
	mOneUpLabelVisible = true;

	mPlayer1Score = new Scoreboard();
	mPlayer1Score->Parent(this);
	mPlayer1Score->Position(-580.0f, 380.0f);

	mPlayer2Score = new Scoreboard();
	mPlayer2Score->Parent(this);
	mPlayer2Score->Position(-200.0f, 380.0f);

	mTanks = new GameEntity();
	mTanks->Parent(this);
	mTanks->Position(-510.0f, 836.0f);

	for (int i = 0; i < MAX_TANK_TEXTURES; i++) {
		mTankTextures[i] = new GLTexture("InvaderSprites.png", 278, 228, 28, 17);
		mTankTextures[i]->Parent(mTanks);
		mTankTextures[i]->Position(-30.0f * (i % 5), 894.0f * (i / 5));
		//mTankTextures[i]->Scale(Vector2(1.5f, 1.5f));
	}

	mTotalTanksLabel = new Scoreboard();
	mTotalTanksLabel->Parent(this);
	mTotalTanksLabel->Position(-460.0f, 836.0f);

	mFlags = new GameEntity();
	mFlags->Parent(this);
	mFlags->Position(-320.0f, 836.0f);

	mFlagTimer = 0.0f;
	mFlagInterval = 0.25f;
}

PlaySideBar::~PlaySideBar() {
	mTimer = nullptr;
	mAudio = nullptr;

	delete mTopBackground;
	mTopBackground = nullptr;

	delete mBottomBackground;
	mBottomBackground = nullptr;

	delete mHighLabel;
	mHighLabel = nullptr;

	delete mP1ScoreLabel;
	mP1ScoreLabel = nullptr;

	delete mP2ScoreLabel;
	mP2ScoreLabel = nullptr;

	delete mHighScoreBoard;
	mHighScoreBoard = nullptr;

	delete mOneUpLabel;
	mOneUpLabel = nullptr;

	delete mPlayer1Score;
	mPlayer1Score = nullptr;

	delete mPlayer2Score;
	mPlayer2Score = nullptr;

	delete mTanks;
	mTanks = nullptr;

	delete mTotalTanksLabel;
	mTotalTanksLabel = nullptr;

	for (auto texture : mTankTextures) {
		delete texture;
		texture = nullptr;
	}

	delete mFlags;
	mFlags = nullptr;

	ClearFlags();
}

void PlaySideBar::ClearFlags() {
	for (int i = 0; i < mFlagTextures.size(); i++) {
		delete mFlagTextures[i];
		mFlagTextures[i] = nullptr;
	}

	mFlagTextures.clear();
}

void PlaySideBar::AddNextFlag() {
	if (mRemainingLevels >= 50) {
		AddFlag("LevelFlags.png", 62, 50);
	}
	else if (mRemainingLevels >= 30) {
		AddFlag("LevelFlags.png", 62, 30);
	}
	else if (mRemainingLevels >= 20) {
		AddFlag("LevelFlags.png", 62, 20);
	}
	else if (mRemainingLevels >= 10) {
		AddFlag("LevelFlags.png", 54, 10);
	}
	else if (mRemainingLevels >= 5) {
		AddFlag("LevelFlags.png", 30, 5);
	}
	else {
		AddFlag("LevelFlags.png", 30, 1);
	}
}

void PlaySideBar::AddFlag(std::string filename, float width, int value) {
	int index = (int)mFlagTextures.size();

	if (index > 0) {
		mFlagXOffset += width * 0.5f;
	}

	if (mFlagXOffset > 450) {		//max width orig 140
		mFlagYOffset += 55;			//moves to next row orig 66
		mFlagXOffset = 0;			//resets x position for new row
	}

	mRemainingLevels -= value;
	int x = 0;

	switch (value) {
	case 50:
		x = 228;
		break;

	case 30:
		x = 168;
		break;

	case 20:
		x = 108;
		break;

	case 10:
		x = 56;
		break;

	case 5:
		x = 28;
		break;
	}

	mFlagTextures.push_back(new GLTexture(filename, x, 0, (int)width - 2, 64));
	mFlagTextures[index]->Parent(mFlags);
	mFlagTextures[index]->Position(mFlagXOffset, mFlagYOffset);
	mFlagXOffset += width * 0.5f;

	mAudio->PlaySFX("FlagSound.wav", 0, -1);
}

void PlaySideBar::SetTanks(int tanks) {
	mTotalTanks = tanks;

	if (tanks > MAX_TANK_TEXTURES) {
		mTotalTanksLabel->Score(tanks);
	}
}

void PlaySideBar::SetHighScore(int score) {
	mHighScoreBoard->Score(score);
}

void PlaySideBar::SetPlayerScore(int score) {
	mPlayer1Score->Score(score);
}

void PlaySideBar::SetLevel(int level) {
	ClearFlags();

	mRemainingLevels = level;
	mFlagXOffset = 0.0f;
}

void PlaySideBar::Update() {
	mBlinkTimer += mTimer->DeltaTime();

	if (mBlinkTimer >= mBlinkInterval) {
		mOneUpLabelVisible = !mOneUpLabelVisible;
		mBlinkTimer = 0.0f;
	}

	if (mRemainingLevels > 0) {
		mFlagTimer += mTimer->DeltaTime();

		if (mFlagTimer >= mFlagInterval) {
			AddNextFlag();
			mFlagTimer = 0.0f;
		}
	}
}

void PlaySideBar::Render() {
	mTopBackground->Render();
	mBottomBackground->Render();

	mHighLabel->Render();
	mP1ScoreLabel->Render();
	mP2ScoreLabel->Render();
	mHighScoreBoard->Render();

	if (mOneUpLabelVisible) {
		mOneUpLabel->Render();
	}

	mPlayer1Score->Render();
	mPlayer2Score->Render();

	for (int i = 0; i < MAX_TANK_TEXTURES && i < mTotalTanks; i ++) {
		mTankTextures[i]->Render();
	}

	if (mTotalTanks > MAX_TANK_TEXTURES) {
		mTotalTanksLabel->Render();
	}

	for (auto flag : mFlagTextures) {
		flag->Render();
	}
}