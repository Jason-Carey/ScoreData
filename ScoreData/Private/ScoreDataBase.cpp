// https://github.com/Jason-Carey

#include "ScoreDataBase.h"
#include "Interfaces/ScoreListener.h"

void UScoreDataBase::DeclareScoreListener(TScriptInterface<IScoreListener> ScoreListener)
{
	// Unfortunately TScriptInterface sets the Interface to null for BP-interfaces so an additional check is required
	if (!ScoreListener && !ScoreListener.GetObject()->Implements<UScoreListener>())
	{
		UE_LOG(LogTemp, Warning, TEXT("DeclareScoreListener: %s does not implement %s"), *ScoreListener.GetObject()->GetName(), *UScoreListener::StaticClass()->GetName());
		return;
	}

	FScriptDelegate ScoreDelegate;
	ScoreDelegate.BindUFunction(ScoreListener.GetObject(), GET_FUNCTION_NAME_CHECKED(IScoreListener, OnScoreUpdate));
	OnScoreUpdate.Add(ScoreDelegate);

	FScriptDelegate ScoreMaxDelegate;
	ScoreMaxDelegate.BindUFunction(ScoreListener.GetObject(), GET_FUNCTION_NAME_CHECKED(IScoreListener, OnScoreMaxUpdate));
	OnScoreMaxUpdate.Add(ScoreMaxDelegate);
}

void UScoreDataBase::RemoveScoreListener(TScriptInterface<IScoreListener> ScoreListener)
{
	// Unfortunately TScriptInterface sets the Interface to null for BP-interfaces so an additional check is required
	if (!ScoreListener && !ScoreListener.GetObject()->Implements<UScoreListener>())
	{
		UE_LOG(LogTemp, Warning, TEXT("RemoveScoreListener: %s does not implement %s"), *ScoreListener.GetObject()->GetName(), *UScoreListener::StaticClass()->GetName());
		return;
	}

	OnScoreUpdate.Remove(ScoreListener.GetObject(), GET_FUNCTION_NAME_CHECKED(IScoreListener, OnScoreUpdate));
	OnScoreMaxUpdate.Remove(ScoreListener.GetObject(), GET_FUNCTION_NAME_CHECKED(IScoreListener, OnScoreMaxUpdate));
}
