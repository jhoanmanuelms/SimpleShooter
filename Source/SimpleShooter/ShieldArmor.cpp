// Fill out your copyright notice in the Description page of Project Settings.


#include "ShieldArmor.h"

// Sets default values
AShieldArmor::AShieldArmor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	SetRootComponent(Root);
	Mesh->SetupAttachment(Root);
	Cover = MaxCover;
}

// Called when the game starts or when spawned
void AShieldArmor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShieldArmor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int AShieldArmor::GetCover() const
{
	return Cover;
}

int AShieldArmor::AbsorbDamage(int Damage)
{
	Cover -= Damage;

	if (Cover < 0) Destroy();

	return Cover;
}
