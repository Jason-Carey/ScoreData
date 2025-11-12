// https://github.com/Jason-Carey

#pragma once

#include "CoreMinimal.h"
#include "ScoreDataBase.h"
#include "ScoreData.generated.h"

/** Encapsulates all the information required for an object's score. */
UCLASS(EditInlineNew, Blueprintable, BlueprintType)
class SCOREDATA_API UScoreData : public UScoreDataBase
{
	GENERATED_BODY()

public:
	/** Set the current score awarded by this object. */
	UFUNCTION(BlueprintSetter)
	virtual void SetScore(int32 Value);

	/** Current score awarded by this object. */
	UFUNCTION(BlueprintGetter)
	virtual int32 GetScore() const override;

	/** Maximum score this object awards. */
	UFUNCTION(BlueprintGetter)
	virtual int32 GetScoreMax() const override;

protected:
	/** Current score awarded by this object. */
	UPROPERTY(BlueprintGetter=GetScore, BlueprintSetter=SetScore)
	int32 Score;

	/** Maximum score this object awards. */
	UPROPERTY(EditDefaultsOnly, BlueprintGetter=GetScoreMax, meta=(ClampMin="0", DisplayName="Maximum Score"))
	int32 ScoreMax;
};
