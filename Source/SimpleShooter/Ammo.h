// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UtilityKit.h"
#include "Ammo.generated.h"

UCLASS()
class SIMPLESHOOTER_API AAmmo : public AUtilityKit
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAmmo();

protected:
	virtual void KitEffect(class AShooterCharacter* Player) override;
};
