#include "TriggerActor.h"
#include "Components/BoxComponent.h"

ATriggerActor::ATriggerActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	RootComponent = TriggerBox;

	TriggerBox->InitBoxExtent(FVector(50.0f, 50.0f, 50.0f));
	TriggerBox->SetCollisionProfileName(TEXT("Trigger"));

	

}

void ATriggerActor::BeginPlay()
{
	Super::BeginPlay();
	if(Actor->GetClass()->ImplementsInterface(UITriggerInterface::StaticClass()))
	{
		// Bind events
		TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ATriggerActor::OnOverlapBegin);
		TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ATriggerActor::OnOverlapEnd);
	}
}

void ATriggerActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		IITriggerInterface::Execute_StartTrigger(Actor);
	}
}

void ATriggerActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		IITriggerInterface::Execute_StartInverseTrigger(Actor);
	}
}

