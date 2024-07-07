#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlatformGameMode.generated.h"

UCLASS()
class PLATFORMGAME_API APlatformGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	APlatformGameMode();
	
	UFUNCTION(BlueprintCallable)
	void SpawnandPosses();
};
