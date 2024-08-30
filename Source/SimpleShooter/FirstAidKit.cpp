// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstAidKit.h"

#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterCharacter.h"

// Sets default values
AFirstAidKit::AFirstAidKit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	SetRootComponent(Root);
	Mesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AFirstAidKit::BeginPlay()
{
	Super::BeginPlay();
	Mesh->OnComponentHit.AddDynamic(this, &AFirstAidKit::OnHit);
}

// Called every frame
void AFirstAidKit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// TODO make it rotate vertically (check toon taks tower rotation)

	// FRotator Rotation = GetActorRotation();
	// FRotator NewRotation = FRotator(Rotation.Pitch + 1, Rotation.Yaw, Rotation.Roll);
	// FQuat QuatRotation = FQuat(NewRotation);
	
	// AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);
}

void AFirstAidKit::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AShooterCharacter* Player = Cast<AShooterCharacter>(OtherActor);

	if (Player)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HealingFlash, GetActorLocation(), GetActorRotation());
		Player->Heal(Healing);
		Destroy();
	}
}
