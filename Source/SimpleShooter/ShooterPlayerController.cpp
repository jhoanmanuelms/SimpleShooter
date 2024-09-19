// Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterPlayerController.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "SimpleShooterGameInstance.h"
#include "TimerManager.h"

void AShooterPlayerController::BeginPlay()
{
	Super::BeginPlay();

	HUD = AddWidget(HUDClass);
}

void AShooterPlayerController::Tick(float DeltaTime)
{
	// TODO use a timer instead of the delta time
	GameTime += DeltaTime;
}

float AShooterPlayerController::GetGameTime() const
{
	return GameTime;
}

void AShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	TSubclassOf<UUserWidget> EndGameWidgetClass = bIsWinner ? WinScreenClass : LoseScreenClass;

	if (bIsWinner) SetBestTime();
	GameTime = 0;

	HUD->RemoveFromViewport();
	AddWidget(EndGameWidgetClass);
	GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
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

void AShooterPlayerController::SetBestTime()
{
	USimpleShooterGameInstance* GameInstance = Cast<USimpleShooterGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (GameInstance != nullptr && !GameInstance->IsBestTimeSet() || GameTime < GameInstance->GetBestTime())
	{
		GameInstance->SetBestTime(GameTime);
	}
}
