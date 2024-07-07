#include "DestroyableCube.h"

ADestroyableCube::ADestroyableCube()
{
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DestroyableCube"));
	RootComponent = MeshComponent;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
	if (CubeMesh.Succeeded())
	{
		MeshComponent->SetStaticMesh(CubeMesh.Object);
	}
	MeshComponent->SetWorldScale3D(FVector(0.5f, 0.1f, 0.5f));
	MeshComponent->SetCollisionProfileName(TEXT("BlockAllDynamic"));
}

void ADestroyableCube::BeginPlay()
{
	Super::BeginPlay();
	Health = 2;
}

void ADestroyableCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADestroyableCube::Hit_Implementation()
{
	Health--;
	UE_LOG(LogTemp,Warning,TEXT("Hit the Box"));
	// /Script/Engine.Material'/Game/Custom/Materials/CustomBlue.CustomBlue'
	FString MaterialPath = TEXT("Material'/Game/Custom/Materials/CustomRed.CustomRed'");
	UObject* ClassMaterial = LoadObject<UMaterial>(nullptr,*MaterialPath);
	UMaterial* Material = Cast<UMaterial>(ClassMaterial);

	
	if(Material)
	{
		MeshComponent->SetMaterial(0,Material);
	}

	if (Health<=0)
	{
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
	}
}
