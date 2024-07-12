// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();

	if (AIBehavior != nullptr)
	{
		RunBehaviorTree(AIBehavior);

		APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		if (PlayerPawn != nullptr)
		{
			GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
		}
	}
}

void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn != nullptr)
	{
		if (LineOfSightTo(PlayerPawn))
		{
			FVector PlayerLocation = PlayerPawn->GetActorLocation();
			GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerLocation);
			GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnonwPlayerLocation"), PlayerLocation);
		}
		else
		{
			GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
		}
	}
}
