#pragma once

#include "CoreMinimal.h"
#include "GameFramework/MovementComponent.h"
#include "CustomMovementComponent.generated.h"


UCLASS(BlueprintType, Blueprintable, meta = (BlueprintSpawnableComponent))
class PLATFORMGAME_API UCustomMovementComponent : public UMovementComponent
{
	GENERATED_BODY()

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float RadiusSphereDetect;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TEnumAsByte<ECollisionChannel> GroundCollisionChanel;

	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	bool bIsGrounded;

	const FVector Gravity = { 0,0,-9.81f };

	UFUNCTION(BlueprintCallable)
	void MovePawn(FVector MoveDirection, float Input);
	UFUNCTION(BlueprintCallable)
	void StopPawn();
	
	UFUNCTION(BlueprintCallable)
	void Jump(float JumpForce);

};
