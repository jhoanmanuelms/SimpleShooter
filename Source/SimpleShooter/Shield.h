// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Shield.generated.h"

UCLASS()
class SIMPLESHOOTER_API AShield : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShield();

	int GetCover() const;
	int AbsorbDamage(int Damage);

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly)
	int MaxCover = 100;

	UPROPERTY(EditAnywhere)
	int Cover;
};
