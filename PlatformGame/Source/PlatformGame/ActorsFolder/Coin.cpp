#include "Coin.h"

#include "Components/SphereComponent.h"
#include "GameFramework/GameSession.h"
#include "Kismet/GameplayStatics.h"
#include "PlatformGame/PlatformGameModeSettings/PlatformPlayerController.h"
#include "PlatformGame/PlatformPawn/PlatformPawn.h"

ACoin::ACoin()
{
	PrimaryActorTick.bCanEverTick = true;
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Coin"));
	RootComponent = MeshComponent;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
	if (SphereMesh.Succeeded())
	{
		MeshComponent->SetStaticMesh(SphereMesh.Object);
	}
	
	MeshComponent->SetWorldScale3D(FVector(0.5f, 0.1f, 0.5f));
	
	SphereColliderComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereColliderComponent->InitSphereRadius(250.f);
	SphereColliderComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	SphereColliderComponent->SetupAttachment(RootComponent);
	SphereColliderComponent->OnComponentBeginOverlap.AddDynamic(this, &ACoin::OnOverlapBegin);
}

void ACoin::BeginPlay()
{
	Super::BeginPlay();
	
	
}

void ACoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FRotator Rotation = GetActorRotation();
	Rotation.Yaw += DeltaTime * 90;  
	SetActorRotation(Rotation);
}

void ACoin::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherActor->ActorHasTag("Player"))
	{
		APlatformPlayerController* PlayerController = Cast<APlatformPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		if (PlayerController)
		{
			PlayerController->AddCoin();
			Collect();
		}
	}
}

void ACoin::Collect()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
}

