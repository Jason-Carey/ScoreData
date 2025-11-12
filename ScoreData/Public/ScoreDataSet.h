// https://github.com/Jason-Carey

#pragma once

#include "CoreMinimal.h"
#include "ScoreDataBase.h"
#include "Interfaces/ScoreListener.h"
#include "ScoreDataSet.generated.h"

/** Aggregates scores into a total set score. */
UCLASS(Blueprintable, BlueprintType)
class SCOREDATA_API UScoreDataSet : public UScoreDataBase, public IScoreListener
{
	GENERATED_BODY()

public:
	UScoreDataSet() = default;
	
	/** Add score to include in the calculations. */
	FSetElementId Add(TScriptInterface<IScore> ScoreData);
	
	/** Remove score from the calculations. */
	bool Remove(const FSetElementId& SetElementId);

	/** Check if the SetElementId is valid. */
	inline bool Contains(const FSetElementId& SetElementId) const;

	/** Get score at the specified SetElementId. */
	inline TScriptInterface<IScore> Get(const FSetElementId& SetElementId) const;

	/** Get score at the specified SetElementId. SetElementId must be valid. */
	inline TScriptInterface<IScore> GetChecked(const FSetElementId& SetElementId) const;
	
	/** Copy score(s) into an array. */
	UFUNCTION(BlueprintCallable)
	TArray<TScriptInterface<IScore>> Array() const;
	
	UFUNCTION(BlueprintGetter)
	virtual inline int32 GetScore() const override;
	
	UFUNCTION(BlueprintGetter)
	virtual inline int32 GetScoreMax() const override;

protected:
	/** Set the system score when an entry is updated. */
	virtual void OnScoreUpdate_Implementation(int32 NewScore, int32 OldScore) override;

	/** Set the system maximum score when an entry is updated. */
	virtual void OnScoreMaxUpdate_Implementation(int32 NewMaxScore, int32 OldMaxScore) override;
	
	/** Sets the current score and preforms a callback. */
	void SetScore(const int32 Value);
	
	/** Sets the maximum score and preforms a callback. */
	void SetScoreMax(const int32 Value);

	/** TScriptInterface isn't supported in TSet, but it's just a UObject wrapper anyway. */
	UPROPERTY(Transient)
	TSet<TObjectPtr<UObject>> Set;
	
	UPROPERTY(Transient, BlueprintGetter=GetScore)
	int32 Score;
	
	UPROPERTY(Transient, BlueprintGetter=GetScoreMax)
	int32 ScoreMax;
};

inline bool UScoreDataSet::Contains(const FSetElementId& SetElementId) const
{
	return Set.IsValidId(SetElementId);
}

inline TScriptInterface<IScore> UScoreDataSet::Get(const FSetElementId& SetElementId) const
{
	return Contains(SetElementId) ? Set[SetElementId] : nullptr;
}

inline TScriptInterface<IScore> UScoreDataSet::GetChecked(const FSetElementId& SetElementId) const
{
	return Set[SetElementId];
}

inline int32 UScoreDataSet::GetScore() const
{
	return Score;
}

inline int32 UScoreDataSet::GetScoreMax() const
{
	return ScoreMax;
}