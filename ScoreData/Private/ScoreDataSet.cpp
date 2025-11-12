// https://github.com/Jason-Carey

#include "ScoreDataSet.h"

// ReSharper disable once CppPassValueParameterByConstReference
FSetElementId UScoreDataSet::Add(TScriptInterface<IScore> ScoreData)
{
	FSetElementId SetElementId;

	// TO-DO: Nested occurrences are possible within the composite pattern
	// - and are not currently well accounted for... union-ing sets could be a way to manage it
	if (ScoreData != nullptr && ScoreData.GetObject() != this)
	{
		const TObjectPtr<UObject>& Obj = ScoreData.GetObject();
		
		SetElementId = Set.FindId(Obj);

		if (!Set.IsValidId(SetElementId))
		{
			// Add this item to the score
			SetScore(GetScore() + ScoreData->GetScore());
			SetScoreMax(GetScoreMax() + ScoreData->GetScoreMax());

			// Bind to score changes
			ScoreData->DeclareScoreListener(this);
			SetElementId = Set.Add(Obj);
		}
	}
	
	return SetElementId;
}

bool UScoreDataSet::Remove(const FSetElementId& SetElementId)
{
	const bool bValid = Set.IsValidId(SetElementId);

	if (bValid)
	{
		const TObjectPtr<UObject>& Obj = Set[SetElementId];
		const TScriptInterface<IScore> ScoreData(Obj);

		// Remove this item from the score
		SetScore(GetScore() - ScoreData->GetScore());
		SetScoreMax(GetScoreMax() - ScoreData->GetScoreMax());

		// Unbind from score changes
		ScoreData->RemoveScoreListener(this);
		Set.Remove(SetElementId);
	}

	return bValid;
}

TArray<TScriptInterface<IScore>> UScoreDataSet::Array() const
{
	TArray<TScriptInterface<IScore>> Result;
	Result.Reserve(Set.Num());
	
	for(auto SetIt = Set.CreateConstIterator(); SetIt; ++SetIt)
	{
		Result.Add(*SetIt);
	}
	
	return Result;
}

void UScoreDataSet::OnScoreUpdate_Implementation(int32 NewScore, int32 OldScore) 
{
	// Calculate the difference between the two scores
	const int32 Delta = NewScore - OldScore;
	SetScore(GetScore() + Delta);
}

void UScoreDataSet::OnScoreMaxUpdate_Implementation(int32 NewMaxScore, int32 OldMaxScore)
{
	// Calculate the difference between the two scores
	const int32 Delta = NewMaxScore - OldMaxScore;
	SetScoreMax(GetScoreMax() + Delta);
}

void UScoreDataSet::SetScore(const int32 Value)
{
	const int32 OldScore = Score;
	Score = Value;
	
	if (OldScore != Score)
    {	
		UScoreDataBase::OnScoreUpdate.Broadcast(Score, OldScore);
    }
}

void UScoreDataSet::SetScoreMax(const int32 Value)
{
	const int32 OldScoreMax = ScoreMax;
	ScoreMax = Value;
	
	if (OldScoreMax != ScoreMax)
    {
		UScoreDataBase::OnScoreMaxUpdate.Broadcast(ScoreMax, OldScoreMax);
    }
}
