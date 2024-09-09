// Fill out your copyright notice in the Description page of Project Settings.


#include "Shield.h"
#include "ShooterCharacter.h"

AShield::AShield()
{
	// Default constructor
}

void AShield::KitEffect(AShooterCharacter* Player)
{
	Player->DeployShield(Cover);
}
