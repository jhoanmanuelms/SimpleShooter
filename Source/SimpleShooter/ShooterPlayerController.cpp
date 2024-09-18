// Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterPlayerController.h"

#include "Blueprint/UserWidget.h"
#include "TimerManager.h"

void AShooterPlayerController::BeginPlay()
{
	Super::BeginPlay();

	HUD = AddWidget(HUDClass);
}

void AShooterPlayerController::Tick(float DeltaTime)
{
	GameTime += DeltaTime;
}

float AShooterPlayerController::GetBestTime() const
{
	return BestTime;
}

float AShooterPlayerController::GetGameTime() const
{
	return GameTime;
}

void AShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	TSubclassOf<UUserWidget> EndGameWidgetClass = bIsWinner ? WinScreenClass : LoseScreenClass;

	HUD->RemoveFromViewport();
	AddWidget(EndGameWidgetClass);
	GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
	BestTime = GameTime;
	GameTime = 0;
}

UUserWidget* AShooterPlayerController::AddWidget(TSubclassOf<UUserWidget> WidgetClass)
{
	UUserWidget* Widget = CreateWidget(this, WidgetClass);
	if (Widget != nullptr)
	{
		Widget->AddToViewport();
	}

	return Widget;
}
