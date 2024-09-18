// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	float GetBestTime() const;

	UFUNCTION(BlueprintPure)
	float GetGameTime() const;

	virtual void Tick(float DeltaTime) override;

	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> HUDClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> WinScreenClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> LoseScreenClass;

	UPROPERTY(EditAnywhere)
	float RestartDelay = 5;

	UPROPERTY(VisibleAnywhere)
	float BestTime = 0;

	UPROPERTY(VisibleAnywhere)
	float GameTime = 0;

	UPROPERTY()
	class UUserWidget* HUD;

	FTimerHandle RestartTimer;

	class UUserWidget* AddWidget(TSubclassOf<class UUserWidget> WidgetClass);
};
