// https://github.com/Jason-Carey

#include "ScoreDataSubsystem.h"
#include "ScoreDataSet.h"

UScoreDataSubsystem::UScoreDataSubsystem()
{
	ScoreDataManager = CreateDefaultSubobject<UScoreDataSet>(TEXT("ScoreDataManagerInstance"));
}
