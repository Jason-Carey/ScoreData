// https://github.com/Jason-Carey

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ScoreListener.generated.h"

UINTERFACE(BlueprintType, Blueprintable)
class SCOREDATA_API UScoreListener : public UInterface
{
	GENERATED_BODY()
};

class SCOREDATA_API IScoreListener
{
	GENERATED_BODY()

public:
	/** Callback for when the score is set on a bound UScoreData. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnScoreUpdate(int32 NewScore, int32 OldScore);

	/** Callback for when the score is set on a bound UScoreData. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnScoreMaxUpdate(int32 NewMaxScore, int32 OldMaxScore);
};
