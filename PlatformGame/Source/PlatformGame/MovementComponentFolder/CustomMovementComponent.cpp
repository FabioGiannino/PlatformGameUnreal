#include "CustomMovementComponent.h"

void UCustomMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	FVector Start =  UpdatedComponent->GetRelativeLocation();
	FVector End = Start - FVector(0, 0, 20.0f); 

	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this->GetOwner());  

	this->bIsGrounded = GetWorld()->LineTraceSingleByChannel(
		HitResult, 
		Start, 
		End, 
		ECC_Visibility, 
		CollisionParams
	);
	DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 1);

	if (!this->bIsGrounded)
	{		
		Velocity.Z += Gravity.Z * DeltaTime* 100;	
	}
	
	FHitResult Hit;
		
	if (!SafeMoveUpdatedComponent(Velocity * DeltaTime, this->GetOwner()->GetActorRotation(), true, Hit))
	{
		FVector CompenetrationCorrection = GetPenetrationAdjustment(Hit);		
		ResolvePenetration(CompenetrationCorrection, Hit, UpdatedComponent->GetComponentQuat());
		if (Hit.Normal.Z > 0)
		{
			Velocity.Z = 0;
			this->bIsGrounded=true;
		}
	}
	

}

void UCustomMovementComponent::MovePawn(const FVector MoveDirection, const float Speed)
{
	
	if (MoveDirection.X*this->Velocity.X !=0)
	{
		this->Velocity.X = 0;
	}
	if (MoveDirection.Y*this->Velocity.Y !=0)	
	{
		this->Velocity.Y = 0;
	}
	this->Velocity += MoveDirection*Speed;
	
}

void UCustomMovementComponent::StopPawn()
{
	this->Velocity.X = 0;
	this->Velocity.Y = 0;
}


void UCustomMovementComponent::Jump(float JumpForce)
{
	this->Velocity.Z += JumpForce;
}