// Fill out your copyright notice in the Description page of Project Settings.


#include "UtilityKit.h"

#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterCharacter.h"

// Sets default values
AUtilityKit::AUtilityKit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	SetRootComponent(Root);
	Mesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AUtilityKit::BeginPlay()
{
	Super::BeginPlay();
	Mesh->OnComponentHit.AddDynamic(this, &AUtilityKit::OnHit);
}

// Called every frame
void AUtilityKit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Rotate(DeltaTime);
}

void AUtilityKit::Rotate(float DeltaTime)
{
	FRotator DeltaRotation = FRotator::ZeroRotator; 
	DeltaRotation.Yaw = DeltaTime * TurnRate;
	AddActorLocalRotation(DeltaRotation, true);
}

void AUtilityKit::KitEffect(class AShooterCharacter* Player)
{
	// To be overriden
}

void AUtilityKit::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AShooterCharacter* Player = Cast<AShooterCharacter>(OtherActor);

	if (Player)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ActivationFlash, GetActorLocation(), GetActorRotation());
		KitEffect(Player);
		Destroy();
	}
}
