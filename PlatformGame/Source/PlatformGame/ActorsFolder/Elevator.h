#pragma once

#include "CoreMinimal.h"
#include "ITriggerInterface.h"
#include "GameFramework/Actor.h"
#include "PlatformGame/SaveSystemFolder/Savable.h"
#include "Elevator.generated.h"

UCLASS()
class PLATFORMGAME_API AElevator : public AActor, public ISavable, public IITriggerInterface
{
	GENERATED_BODY()

public:
	AElevator();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	void ApplyForce(FVector ForceToApply);
	virtual void StartTrigger_Implementation();
	virtual void StartInverseTrigger_Implementation();
	
private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComponent;
	UPROPERTY(EditAnywhere)
	FVector Force;
	UPROPERTY(EditAnywhere)
	float Countdown;
	
	float CurrentTimer;
	bool bIsTrigger;
};
