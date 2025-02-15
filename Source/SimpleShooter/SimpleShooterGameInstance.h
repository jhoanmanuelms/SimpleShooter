#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SimpleShooterGameInstance.generated.h"

UCLASS()
class SIMPLESHOOTER_API USimpleShooterGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	float GetBestTime() const;

	UFUNCTION(BlueprintPure)
	FString GetFormattedBestTime() const;

	UFUNCTION(BlueprintPure)
	bool IsBestTimeSet() const;

	void SetBestTime(float fBestTime);

private:
	UPROPERTY(VisibleAnywhere)
	float BestTime = 0;
};
