// Fill out your copyright notice in the Description page of Project Settings.


#include "Ammo.h"
#include "ShooterCharacter.h"

AAmmo::AAmmo()
{
	// Default constructor
}

void AAmmo::KitEffect(AShooterCharacter* Player)
{
	Player->RechargeWeapons();
}
