// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstAidKit.h"
#include "ShooterCharacter.h"

AFirstAidKit::AFirstAidKit()
{
	// Default constructor
}

void AFirstAidKit::KitEffect(AShooterCharacter* Player)
{
	Player->Heal(Healing);
}
