// https://github.com/Jason-Carey

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "ScoreDataSubsystem.generated.h"

class UScoreDataSet;

UCLASS(ClassGroup=(ScoreData))
class SCOREDATA_API UScoreDataSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	UScoreDataSubsystem();

	/** An aggregation of ScoreData for this world. */
	UFUNCTION(BlueprintCallable)
	inline UScoreDataSet* GetScoreDataManager() const;
	
private:
	/** Global set of score data. */
	UPROPERTY(Transient, Instanced)
	TObjectPtr<UScoreDataSet> ScoreDataManager;
};

inline UScoreDataSet* UScoreDataSubsystem::GetScoreDataManager() const
{
	return ScoreDataManager;
}
