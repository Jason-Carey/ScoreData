// https://github.com/Jason-Carey

#include "ScoreDataComponent.h"
#include "ScoreDataSubsystem.h"
#include "ScoreDataSet.h"
#include "ScoreData.h"

UScoreDataComponent::UScoreDataComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	ScoreData = CreateDefaultSubobject<UScoreData>(TEXT("ScoreDataInstance"));
}

void UScoreDataComponent::BeginPlay()
{
	if (bAutoAddToSubsystem)
	{
		AddToSubsystem();
	}
}

void UScoreDataComponent::AddToSubsystem()
{
	const TObjectPtr<UScoreDataSubsystem> ScoreDataSubsystem = GetWorld()->GetSubsystem<UScoreDataSubsystem>();
	check(ScoreDataSubsystem);

	const TObjectPtr<UScoreDataSet> ScoreDataManager = ScoreDataSubsystem->GetScoreDataManager();
	check(ScoreDataManager);

	const bool IsAlreadyAdded = ScoreDataManager->Contains(SetElementId);

	if (!IsAlreadyAdded)
	{
		SetElementId = ScoreDataManager->Add(ScoreData);
	}
}

bool UScoreDataComponent::IsAlreadyInSubsystem() const
{
	return SetElementId.IsValidId();
}
