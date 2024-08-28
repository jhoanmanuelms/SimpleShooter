// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));

	SetRootComponent(Root);
	Mesh->SetupAttachment(Root);
}

AController* AGun::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) return nullptr;

	return OwnerPawn->GetController();
}

bool AGun::GunTrace(FHitResult& Hit, FVector& ShotDirection)
{
	FVector Location;
	FRotator Rotation;
	AController* OwnerController = GetOwnerController();

	if (OwnerController == nullptr) return false;

	OwnerController->GetPlayerViewPoint(Location, Rotation);

	FCollisionQueryParams CollisionParams;
	FVector End = Location + Rotation.Vector() * MaxRange;

	CollisionParams.AddIgnoredActor(this);
	CollisionParams.AddIgnoredActor(GetOwner());

	ShotDirection = -Rotation.Vector();
	bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1, CollisionParams);

	return bHit;
}

int AGun::GetAmmo() const
{
	return Ammo;
}

void AGun::PullTrigger()
{
	if (Ammo > 0)
	{
		UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
		UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFlashSocket"));

		Ammo--;
		FHitResult Hit;
		FVector ShotDirection;
		bool bHit = GunTrace(Hit, ShotDirection);

		if (bHit)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.Location, ShotDirection.Rotation());
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, Hit.Location, ShotDirection.Rotation());

			AActor* HitActor = Hit.GetActor();
			if (HitActor != nullptr)
			{
				AController* OwnerController = GetOwnerController();
				if (OwnerController == nullptr) return;

				FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
				HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
			}
		}
	}
	else
	{
		UGameplayStatics::SpawnSoundAttached(NoAmmoSound, Mesh, TEXT("MuzzleFlashSocket"));
	}
}
