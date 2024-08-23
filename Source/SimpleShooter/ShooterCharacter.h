// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <map>
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class AGun;

UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintPure)
	int GetAmmo();

	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;

	UFUNCTION(BlueprintPure)
	int GetSelectedWeapon() const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Anim)
	class UAnimMontage *SwapWeaponMontage;

	void Shoot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	const int PRIMARY_WEAPON = 1;
	const int SECONDARY_WEAPON = -1;

	void SwapWeapon();
	void SetPrimaryWeapon();
	void SetSecondaryWeapon();
	void SpawnWeapon(int WeaponIndex);
	void SwapWeapon(float AxisValue);
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookUpRate(float AxisValue);
	void LookRightRate(float AxisValue);

	int SelectedWeapon;
	std::map<int, AGun*> Weapons;

	UPROPERTY(EditAnywhere)
	float RotationRate = 70;

	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100;

	UPROPERTY(VisibleAnywhere)
	float Health;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> PrimaryWeaponClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> SecondaryWeaponClass;
};
