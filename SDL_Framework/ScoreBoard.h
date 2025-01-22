#pragma once
#include "GLTexture.h"
#include <vector>

using namespace SDL_Framework;

class Scoreboard : public GameEntity {
public:
	Scoreboard();
	Scoreboard(SDL_Color color);
	~Scoreboard();

	void Score(int score);

	void Render() override;

private:
	void ClearBoard();

	std::vector<GLTexture*> mScore;
	SDL_Color mColor;
};