#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IHittable.generated.h"

UINTERFACE()
class UIHittable : public UInterface
{
	GENERATED_BODY()
};

class PLATFORMGAME_API IIHittable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Hit")
	void Hit();
};
