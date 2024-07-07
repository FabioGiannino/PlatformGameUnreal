#pragma once

#include "CoreMinimal.h"
#include "IHittable.h"
#include "GameFramework/Actor.h"
#include "PlatformGame/SaveSystemFolder/Savable.h"
#include "DestroyableCube.generated.h"

UCLASS()
class PLATFORMGAME_API ADestroyableCube : public AActor, public IIHittable, public ISavable
{
	GENERATED_BODY()

public:
	ADestroyableCube();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void Hit_Implementation();
	
private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComponent;
	UPROPERTY()
	int32 Health;
};
