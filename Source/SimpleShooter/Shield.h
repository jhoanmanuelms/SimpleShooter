// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UtilityKit.h"
#include "Shield.generated.h"

UCLASS()
class SIMPLESHOOTER_API AShield : public AUtilityKit
{
	GENERATED_BODY()

public:
	AShield();

protected:
	virtual void KitEffect(class AShooterCharacter* Player) override;

private:
	UPROPERTY(EditAnywhere)
	float Cover = 50;
};
