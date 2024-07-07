
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ITriggerInterface.generated.h"

UINTERFACE()
class UITriggerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PLATFORMGAME_API IITriggerInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Trigger")
	void StartTrigger();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Trigger")
	void StartInverseTrigger();
};
