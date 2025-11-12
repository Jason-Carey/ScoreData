// https://github.com/Jason-Carey

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Score.generated.h"

class IScoreListener;

// This is intentionally NotBlueprintable because TScriptInterface is null for BP-interfaces use UScoreData for blueprintable.
UINTERFACE(NotBlueprintable, BlueprintType)
class SCOREDATA_API UScore : public UInterface
{
	GENERATED_BODY()
};

class SCOREDATA_API IScore
{
	GENERATED_BODY()

public:
	/** Current score awarded by this object. */
	UFUNCTION(BlueprintCallable)
	virtual int32 GetScore() const = 0;

	/** Maximum score this object awards. */
	UFUNCTION(BlueprintCallable)
	virtual int32 GetScoreMax() const = 0;

	/** Add a listener for when the score is set. */
	UFUNCTION(BlueprintCallable)
	virtual void DeclareScoreListener(TScriptInterface<IScoreListener> ScoreListener) = 0;

	/** Remove a listener to when the score is set. */
	UFUNCTION(BlueprintCallable)
	virtual void RemoveScoreListener(TScriptInterface<IScoreListener> ScoreListener) = 0;
};

