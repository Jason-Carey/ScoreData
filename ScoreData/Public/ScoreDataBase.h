// https://github.com/Jason-Carey

#pragma once
	
#include "CoreMinimal.h"
#include "Interfaces/Score.h"
#include "ScoreDataBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnScoreUpdate, int32, NewScore, int32, OldScore);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnScoreMaxUpdate, int32, NewMaxScore, int32, OldMaxScore);

UCLASS(Abstract, NotBlueprintable)
class SCOREDATA_API UScoreDataBase : public UObject, public IScore
{
	GENERATED_BODY()

public:
	/** Current score awarded by this object. */
	virtual int32 GetScore() const override PURE_VIRTUAL( UScoreDataBase::GetScore, return 0; );

	/** Maximum score this object awards. */
	virtual int32 GetScoreMax() const override PURE_VIRTUAL( UScoreDataBase::GetScoreMax, return 0; );

	/** Add a listener for when the score is set. */
	UFUNCTION(BlueprintCallable)
	virtual void DeclareScoreListener(TScriptInterface<IScoreListener> ScoreListener) override;

	/** Remove a listener to when the score is set. */
	UFUNCTION(BlueprintCallable)
	virtual void RemoveScoreListener(TScriptInterface<IScoreListener> ScoreListener) override;

protected:
	/** Sends score change notifications. */
	UPROPERTY(Transient, BlueprintAssignable)
	FOnScoreUpdate OnScoreUpdate;

	/** Sends maximum score change notifications. */
	UPROPERTY(Transient, BlueprintAssignable)
	FOnScoreMaxUpdate OnScoreMaxUpdate;
};
