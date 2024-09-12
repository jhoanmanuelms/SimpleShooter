// Fill out your copyright notice in the Description page of Project Settings.


#include "ShieldKit.h"
#include "ShooterCharacter.h"

AShieldKit::AShieldKit()
{
	// Default constructor
}

void AShieldKit::KitEffect(AShooterCharacter* Player)
{
	Player->DeployShield();
}
