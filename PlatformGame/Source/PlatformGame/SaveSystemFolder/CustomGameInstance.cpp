#include "CustomGameInstance.h"

#include "CustomSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Savable.h"
#include "PlatformGame/PlatformGameModeSettings/PlatformPlayerController.h"

void UCustomGameInstance::SaveGame()
{
	UCustomSaveGame* SaveGameInstance = Cast<UCustomSaveGame>(UGameplayStatics::CreateSaveGameObject(UCustomSaveGame::StaticClass()));
	if (SaveGameInstance)
	{
		UWorld* World = GetWorld();
		TArray<AActor*> ActorsToSave;
		UGameplayStatics::GetAllActorsWithInterface(World,USavable::StaticClass(),ActorsToSave);

		for (AActor* Actor: ActorsToSave)
		{
			FActorSaveData SaveDataActor;
			SaveDataActor.ActorLocation = Actor->GetActorLocation();
			SaveDataActor.ActorName = Actor->GetFName();
			SaveDataActor.ActorRotator = Actor->GetActorRotation();
			SaveDataActor.bIsActive = !Actor->IsHidden();
			SaveGameInstance->ActorsSaveData.Add(SaveDataActor);
		}
		APlatformPlayerController* PlayerController = Cast<APlatformPlayerController>(UGameplayStatics::GetPlayerController(World,0));
		if(PlayerController)
		{
			SaveGameInstance->PlayerSaveData.PlayerCoin = PlayerController->CollectedCoins; 
		}
		APawn* Pawn = UGameplayStatics::GetPlayerPawn(World,0);
		if (Pawn)
		{
			
			//SaveGameInstance->PlayerSaveData.PlayerLocation = Pawn->GetActorLocation(); NON SO PERCHè MA QUESTO DI PUNTO IN BIANCO HA DECISO DI ROMPERE TUTTO IL SAVEGAME
		}
		UGameplayStatics::SaveGameToSlot(SaveGameInstance, "SaveSlot", 0);

	}
}

void UCustomGameInstance::LoadGame()
{
	UCustomSaveGame* LoadGameInstance = Cast<UCustomSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("SaveSlot"), 0));
	if (LoadGameInstance)
	{
		APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		//PlayerPawn->SetActorLocation(LoadGameInstance->PlayerSaveData.PlayerLocation);
		//PlayerPawn->SetActorRotation(LoadGameInstance->PlayerSaveData.PlayerRotator);
		
		APlatformPlayerController* PlayerController = Cast<APlatformPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(),0));
		if(PlayerController)
		{
			PlayerController->CollectedCoins = LoadGameInstance->PlayerSaveData.PlayerCoin;
			PlayerController->TriggerEvents();
		}
		
		TArray<AActor*> ISavableActorsInScene;
		UGameplayStatics::GetAllActorsWithInterface(GetWorld(),USavable::StaticClass(),ISavableActorsInScene);
		for(FActorSaveData Actor : LoadGameInstance->ActorsSaveData)
		{
			AActor* FoundActor = nullptr;
			for (AActor* ActorInGame : ISavableActorsInScene)
			{
				if (ActorInGame->GetFName() == Actor.ActorName)
				{
					FoundActor = ActorInGame;
					break;
				}
			}

			if (FoundActor)
			{
				if (!Actor.bIsActive)
				{
					FoundActor->SetActorHiddenInGame(true);
					FoundActor->SetActorEnableCollision(false);
					continue;
				}
				
				FoundActor->SetActorHiddenInGame(false);
				FoundActor->SetActorEnableCollision(true);
				FoundActor->SetActorLocation(Actor.ActorLocation);
				FoundActor->SetActorRotation(Actor.ActorRotator);
			}
			else
			{
				//the object has been destroyed
			}
		}
	}
}
