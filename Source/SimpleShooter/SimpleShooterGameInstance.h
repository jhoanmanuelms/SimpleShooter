#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SimpleShooterGameInstance.generated.h"

UCLASS()
class SIMPLESHOOTER_API USimpleShooterGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	float GetBestTime() const;

	void SetBestTime(float fBestTime);

private:
	UPROPERTY(VisibleAnywhere)
	float BestTime = 0;
};
