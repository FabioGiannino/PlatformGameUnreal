#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Pawn.h"
#include "PlatformGame/MovementComponentFolder/CustomMovementComponent.h"
#include "PlatformPawn.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class PLATFORMGAME_API APlatformPawn : public APawn
{
	GENERATED_BODY()

public:
	APlatformPawn();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCustomMovementComponent* MovementComponentInstance;		//LA REFERENCE DEL MOVEMENT COMPONENT
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* SkeletalMeshComponentInstance;	//LA REFERENCE DELLO SCHELETRO
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ImpulseIntensity = 10000;

	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	//UInputAction* LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SaveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LoadAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ShootAction;

	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	
private:
	bool ShootLogic(FVector StartPoint, FVector EndPoint, ECollisionChannel CollisionChannel);
	float CooldownShoot = 1.5f;
	float CurrentTimerShoot = 0.f;

	
protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);
	void Jump(const FInputActionValue& Input);
	void StopMove(const FInputActionValue& Value);
	void Save(const FInputActionValue& Value);
	void Load(const FInputActionValue& Value);
	void Shoot(const FInputActionValue& Value);

	
	

};
