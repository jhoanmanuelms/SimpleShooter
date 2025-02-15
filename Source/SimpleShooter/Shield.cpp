// Fill out your copyright notice in the Description page of Project Settings.


#include "Shield.h"

// Sets default values
AShield::AShield()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	SetRootComponent(Root);
	Mesh->SetupAttachment(Root);
	Cover = MaxCover;
}

float AShield::GetCover() const
{
	return Cover;
}

float AShield::GetCoverPercent() const
{
	return Cover / MaxCover;
}

float AShield::AbsorbDamage(int Damage)
{
	Cover -= Damage;

	return Cover;
}
