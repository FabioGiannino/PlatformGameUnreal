#include "PlatformPlayerController.h"
void APlatformPlayerController::BeginPlay()
{
	Super::BeginPlay();
	CollectedCoins= 0;
}

void APlatformPlayerController::TriggerEvents()
{
	OnPickUpCoin.Broadcast(CollectedCoins);
}

void APlatformPlayerController::AddCoin()
{
	CollectedCoins++;
	TriggerEvents();
}
