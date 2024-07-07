#include "PlatformGameMode.h"
#include "PlatformPlayerController.h"


APlatformGameMode::APlatformGameMode()
{
	FString PawnPath = TEXT("Blueprint'/Game/Custom/BP_PlatformerPawn.BP_PlatformerPawn_C'");
	UClass* PawnClass = LoadClass<APawn>(nullptr,*PawnPath);
	if (PawnClass)
	{	
		DefaultPawnClass = PawnClass;
	}
	this->PlayerControllerClass =APlatformPlayerController::StaticClass();
}

void APlatformGameMode::SpawnandPosses()
{
	FString PawnPath = TEXT("Blueprint'/Game/Custom/BP_PlatformerPawn.BP_PlatformerPawn_C'");
	UClass* PawnClass = LoadClass<APawn>(nullptr,*PawnPath);
	if (PawnClass) 
	{
		APawn* NewPawn=GetWorld()->SpawnActor<APawn>(PawnClass);
		if (NewPawn) 
		{
			GetWorld()->GetFirstPlayerController()->Possess(NewPawn);
		}
	}
}
