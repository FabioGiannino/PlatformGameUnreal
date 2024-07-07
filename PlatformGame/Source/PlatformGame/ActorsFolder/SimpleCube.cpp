#include "SimpleCube.h"


ASimpleCube::ASimpleCube()
{
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SimpleCube"));
	RootComponent = MeshComponent;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
	if (CubeMesh.Succeeded())
	{
		MeshComponent->SetStaticMesh(CubeMesh.Object);
	}
	MeshComponent->SetWorldScale3D(FVector(1.f, 1.f, 1.f));
	MeshComponent->SetCollisionProfileName(TEXT("BlockAllDynamic"));
}

void ASimpleCube::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASimpleCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

