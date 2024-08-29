// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstAidKit.h"

#include "ShooterCharacter.h"
#include "Components/StaticMeshComponent.h"

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
}

void AFirstAidKit::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Display, TEXT("first aid hit"));
	AShooterCharacter* Player = Cast<AShooterCharacter>(OtherActor);

	if (Player)
	{
		// TODO add particle effect (look for particles in the asset packs)
		// TODO implement heal in the shooter character
		UE_LOG(LogTemp, Display, TEXT("by the player"));
		Destroy();
	}
}
