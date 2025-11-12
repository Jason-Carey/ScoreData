// https://github.com/Jason-Carey

#include "ScoreData.h"

void UScoreData::SetScore(int32 Value)
{
	const int32 OldScore = Score;
	Score = FMath::Clamp(Value, 0, ScoreMax);

	if (Score != OldScore)
	{
		UScoreDataBase::OnScoreUpdate.Broadcast(Score, OldScore);
	}
}

int32 UScoreData::GetScore() const
{
	return Score;
}

int32 UScoreData::GetScoreMax() const
{
	return ScoreMax;
}
