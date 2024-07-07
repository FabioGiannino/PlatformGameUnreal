#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlatformGame/SaveSystemFolder/Savable.h"
#include "SimpleCube.generated.h"

UCLASS()
class PLATFORMGAME_API ASimpleCube : public AActor, public ISavable
{
	GENERATED_BODY()

public:
	ASimpleCube();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComponent;
};
