#include "precomp.h"
#include "scoreManager.h"
#include "textRenderer.h"


void ScoreManager::IncrementScore(int value) 
{ 
	_score += value; 
	_rend->SetText(_converter.SetString(_score));
}

void ScoreManager::DecrementScore(int value)
{
	_score -= value;
	_rend->SetText(_converter.SetString(_score));
}

void ScoreManager::SetScore(int score)
{
	_score = score;
	_rend->SetText(_converter.SetString(_score));
}

void ScoreManager::ResetScore() 
{ 
	_score = 0; 
	_rend->SetText(_converter.SetString(_score));
}
