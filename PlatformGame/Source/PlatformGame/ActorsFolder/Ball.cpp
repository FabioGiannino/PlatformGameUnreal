#include "Ball.h"

ABall::ABall()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABall::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

