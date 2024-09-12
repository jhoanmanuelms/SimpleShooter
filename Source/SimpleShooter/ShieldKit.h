// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UtilityKit.h"
#include "ShieldKit.generated.h"

UCLASS()
class SIMPLESHOOTER_API AShieldKit : public AUtilityKit
{
	GENERATED_BODY()

public:
	AShieldKit();

protected:
	virtual void KitEffect(class AShooterCharacter* Player) override;
};
