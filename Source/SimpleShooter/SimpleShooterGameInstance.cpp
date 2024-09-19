#include "SimpleShooterGameInstance.h"

float USimpleShooterGameInstance::GetBestTime() const
{
	return BestTime;
}

bool USimpleShooterGameInstance::IsBestTimeSet() const
{
	return BestTime != 0;
}

void USimpleShooterGameInstance::SetBestTime(float fBestTime)
{
	BestTime = fBestTime;
}
