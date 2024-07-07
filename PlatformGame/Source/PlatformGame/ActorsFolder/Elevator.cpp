#include "Elevator.h"

AElevator::AElevator()
{
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ElevatorMesh"));
	RootComponent = MeshComponent;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
	if (CubeMesh.Succeeded())
	{
		MeshComponent->SetStaticMesh(CubeMesh.Object);
	}
	MeshComponent->SetWorldScale3D(FVector(1.f, 1.f, 0.2f));
	MeshComponent->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	MeshComponent->SetSimulatePhysics(true);
	MeshComponent->SetMassOverrideInKg(NAME_None, 10);
}

void AElevator::BeginPlay()
{
	Super::BeginPlay();
	CurrentTimer =0;
}
void AElevator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(bIsTrigger)
	{
		CurrentTimer += DeltaTime;
		ApplyForce(Force);
		if (CurrentTimer>= Countdown)
		{
			CurrentTimer = 0;
			bIsTrigger = false;
			FVector AntiForce= Force*-1;
			MeshComponent->SetPhysicsLinearVelocity(FVector::Zero());
			ApplyForce(AntiForce);
		}
	}
}

void AElevator::ApplyForce(FVector ForceToApply)
{
	MeshComponent->AddForce(ForceToApply);
}

void AElevator::StartTrigger_Implementation()
{
	bIsTrigger = true;
	ApplyForce(Force);
}

void AElevator::StartInverseTrigger_Implementation()
{
	//	bIsTrigger = true;
}

