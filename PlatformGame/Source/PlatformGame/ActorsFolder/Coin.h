#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlatformGame/SaveSystemFolder/Savable.h"
#include "Components/SphereComponent.h"
#include "Coin.generated.h"

UCLASS()
class PLATFORMGAME_API ACoin : public AActor, public ISavable
{
	GENERATED_BODY()

public:
	ACoin();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComponent;
	
	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereColliderComponent;
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
						UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
						bool bFromSweep, const FHitResult& SweepResult);

	void Collect();
};
