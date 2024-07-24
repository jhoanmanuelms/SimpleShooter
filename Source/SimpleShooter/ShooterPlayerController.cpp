// Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterPlayerController.h"

#include "Blueprint/UserWidget.h"
#include "TimerManager.h"

void AShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	TSubclassOf<class UUserWidget> ScreenClass = bIsWinner ? WinScreenClass : LoseScreenClass;
	UUserWidget* Screen = CreateWidget(this, ScreenClass);
	if (Screen != nullptr)
	{
		Screen->AddToViewport();
	}

	GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}
