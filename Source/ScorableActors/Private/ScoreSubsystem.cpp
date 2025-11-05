// https://github.com/Jason-Carey

#include "ScoreSubsystem.h"

FScoreDataId UScoreSubsystem::DeclareScoreData(TScriptInterface<IScoreData> ScoreData)
{
	FScoreDataId ScoreDataId;

	if (ScoreData != nullptr)
	{
		ScoreDataId = ScoreData->GetId();

		if (!ScoreDataMap.Contains(ScoreDataId))
		{
			// Calculate and set the maximum system score
			const int32 ScoreMax = GetSystemScoreMax() + ScoreData->GetScoreMax();
			SetSystemScoreMax(ScoreMax);

			// Bind to score changes
			ScoreData->DeclareScoreListener(this);
		}
	}

	return ScoreDataId;
}

bool UScoreSubsystem::RemoveScoreData(const FScoreDataId& ScoreDataId)
{
	const TScriptInterface<IScoreData>* ScoreDataPtr = ScoreDataMap.Find(ScoreDataId);
	const bool bValid = ScoreDataPtr != nullptr;

	if (bValid)
	{
		const TScriptInterface<IScoreData>& ScoreData = *ScoreDataPtr;

		// Calculate and set the current system score
		const int32 Score = GetSystemScore() - ScoreData->GetScore();
		SetSystemScore(Score);
		
		// Calculate and set the maximum system score
		const int32 ScoreMax = GetSystemScoreMax() - ScoreData->GetScoreMax();
		SetSystemScoreMax(ScoreMax);

		// Unbind from score changes
		ScoreData->RemoveScoreListener(this);

		// Remove from the system
		ScoreDataMap.Remove(ScoreDataId);
	}

	return bValid;
}

void UScoreSubsystem::OnScoreSet(int32 PrevScore, int32 NewScore)
{
	// Calculate the difference between the two scores
	const int32 Delta = NewScore - PrevScore;
	
	// Add the difference between the two scores to the current system score
	const int32 Score = GetSystemScore() + Delta;
	SetSystemScore(Score);
}

int32 UScoreSubsystem::GetSystemScore() const
{
	return SystemScore;
}

int32 UScoreSubsystem::GetSystemScoreMax() const
{
	return SystemScoreMax;
}

void UScoreSubsystem::SetSystemScore(const int32 Value)
{
	const int32 PrevScore = SystemScore;
	SystemScore = Value;
	
	if (PrevScore != SystemScore)
    {	
        OnSystemScoreSet.Broadcast(PrevScore, SystemScore);
    }
}

void UScoreSubsystem::SetSystemScoreMax(const int32 Value)
{
	const int32 PrevScoreMax = SystemScoreMax;
	SystemScoreMax = Value;
	
	if (PrevScoreMax != SystemScoreMax)
    {	
        OnSystemScoreMaxSet.Broadcast(PrevScoreMax, SystemScoreMax);
    }
}
