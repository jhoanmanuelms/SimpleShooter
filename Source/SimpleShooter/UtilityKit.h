// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UtilityKit.generated.h"

UCLASS()
class SIMPLESHOOTER_API AUtilityKit : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUtilityKit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void KitEffect(class AShooterCharacter* Player);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void Rotate(float DeltaTime);

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	UParticleSystem* ActivationFlash;

	UPROPERTY(EditAnywhere)
	float TurnRate = 60.f;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
