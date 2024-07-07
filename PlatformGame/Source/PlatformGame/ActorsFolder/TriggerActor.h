#pragma once

#include "CoreMinimal.h"
#include "ITriggerInterface.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "TriggerActor.generated.h"

UCLASS()
class PLATFORMGAME_API ATriggerActor : public AActor
{
	GENERATED_BODY()

public:
	ATriggerActor();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere)
	AActor* Actor;
	
	IITriggerInterface* ActorToActivate;

private:
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* TriggerBox;
	
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, 
						class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, 
						const FHitResult & SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, 
					  class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
