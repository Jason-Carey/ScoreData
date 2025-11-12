// https://github.com/Jason-Carey

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ScoreDataComponent.generated.h"

class UScoreData;

UCLASS(ClassGroup=(ScoreData), meta=(BlueprintSpawnableComponent))
class SCOREDATA_API UScoreDataComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UScoreDataComponent();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void AddToSubsystem();
	
	UFUNCTION(BlueprintCallable)
	bool IsAlreadyInSubsystem() const;

	/** Implementation of how this component manages score. */
	UPROPERTY(EditDefaultsOnly, Instanced, BlueprintReadWrite)
	TObjectPtr<UScoreData> ScoreData;

	/** Should this component automatically be added to the score subsystem. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bAutoAddToSubsystem = true;
	
	/** Set ID position within the subsystem. */
	FSetElementId SetElementId;
};