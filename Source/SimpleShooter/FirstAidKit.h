// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UtilityKit.h"
#include "FirstAidKit.generated.h"

UCLASS()
class SIMPLESHOOTER_API AFirstAidKit : public AUtilityKit
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFirstAidKit();

protected:
	virtual void KitEffect(class AShooterCharacter* Player) override;

private:
	UPROPERTY(EditAnywhere)
	float Healing = 120;
};
