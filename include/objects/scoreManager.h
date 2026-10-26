#pragma once

#include "textConverter.h"

class TextRenderer;

class ScoreManager
{
public:

	// Logic
	void IncrementScore(int value);
	void DecrementScore(int value);

	void SetScore(int score);
	void ResetScore();

	// Getters & Setters
	int GetScore() const { return _score; }
	void SetRenderer(TextRenderer& rend) { _rend = &rend; }

private:

	int _score = 0;
	TextRenderer* _rend;
	TextConverter _converter;
};