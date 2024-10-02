#include "SimpleShooterGameInstance.h"

float USimpleShooterGameInstance::GetBestTime() const
{
	return BestTime;
}

FString USimpleShooterGameInstance::GetFormattedBestTime() const
{
	FTimespan TimeSpan = FTimespan(0, 0, BestTime);
	return TimeSpan.ToString(TEXT("%m:%s"));
}

bool USimpleShooterGameInstance::IsBestTimeSet() const
{
	return BestTime != 0;
}

void USimpleShooterGameInstance::SetBestTime(float fBestTime)
{
	BestTime = fBestTime;
}
