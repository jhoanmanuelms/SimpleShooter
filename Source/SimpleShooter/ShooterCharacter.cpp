// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"

#include "Components/CapsuleComponent.h"
#include "Gun.h"
#include "SimpleShooterGameModeBase.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	Weapons[PRIMARY_WEAPON] = GetWorld()->SpawnActor<AGun>(PrimaryWeaponClass);
	Weapons[SECONDARY_WEAPON] = GetWorld()->SpawnActor<AGun>(SecondaryWeaponClass);

	SpawnWeapon(PRIMARY_WEAPON);

	// Hide unnecessary animation bone
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
}

void AShooterCharacter::SpawnWeapon(int WeaponIndex)
{
	// TODO montage blend space to change guns while moving
	if (SwapWeaponMontage)
	{
		PlayAnimMontage(SwapWeaponMontage, 1, NAME_None);
	}

	SelectedWeapon = WeaponIndex;
	Weapons[-SelectedWeapon]->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
	Weapons[SelectedWeapon]->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Weapons[SelectedWeapon]->SetOwner(this);
}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Shoot);

	PlayerInputComponent->BindAxis(TEXT("SwapWeapon"), this, &AShooterCharacter::SwapWeapon);
	PlayerInputComponent->BindAction(TEXT("SwapWeaponController"), EInputEvent::IE_Pressed, this, &AShooterCharacter::SwapWeapon);
	PlayerInputComponent->BindAction(TEXT("PrimaryWeapon"), EInputEvent::IE_Pressed, this, &AShooterCharacter::SetPrimaryWeapon);
	PlayerInputComponent->BindAction(TEXT("SecondaryWeapon"), EInputEvent::IE_Pressed, this, &AShooterCharacter::SetSecondaryWeapon);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShooterCharacter::MoveRight);

	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);

	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &AShooterCharacter::LookUpRate);
	PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &AShooterCharacter::LookRightRate);
}

float AShooterCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	float DamageApplied = FMath::Min(Health, DamageToApply);

	Health -= DamageApplied;
	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), Health);

	if (IsDead())
	{
		ASimpleShooterGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ASimpleShooterGameModeBase>();
		if (GameMode != nullptr)
		{
			GameMode->PawnKilled(this);
		}

		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	return DamageApplied;
}

bool AShooterCharacter::IsDead() const
{
	return Health <= 0;
}

int AShooterCharacter::GetAmmo()
{
	return Weapons[SelectedWeapon]->GetAmmo();
}

int AShooterCharacter::GetSelectedWeapon() const
{
	return (SelectedWeapon == PRIMARY_WEAPON) ? 0 : 1;
}

float AShooterCharacter::GetHealthPercent() const
{
	return Health / MaxHealth;
}

void AShooterCharacter::Shoot()
{
	Weapons[SelectedWeapon]->PullTrigger();
}

void AShooterCharacter::RechargeWeapons()
{
	for (auto& Weapon : Weapons)
	{
		Weapon.second->Recharge();
	}
}

void AShooterCharacter::Heal(int Healing)
{
	Health = std::min(MaxHealth, (Health + Healing));
}

void AShooterCharacter::SwapWeapon()
{
	SpawnWeapon(-SelectedWeapon);
}

void AShooterCharacter::SwapWeapon(float AxisValue)
{
	if (AxisValue != 0)
	{
		SwapWeapon();
	}
}

void AShooterCharacter::SetPrimaryWeapon()
{
	SpawnWeapon(PRIMARY_WEAPON);
}

void AShooterCharacter::SetSecondaryWeapon()
{
	SpawnWeapon(SECONDARY_WEAPON);
}

void AShooterCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AShooterCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void AShooterCharacter::LookUpRate(float AxisValue)
{
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::LookRightRate(float AxisValue)
{
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}
