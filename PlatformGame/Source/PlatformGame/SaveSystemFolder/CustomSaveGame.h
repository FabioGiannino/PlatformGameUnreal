#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "CustomSaveGame.generated.h"
USTRUCT(BlueprintType)
struct FPlayerSaveData {
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite)
	FVector PlayerLocation;
	UPROPERTY(BlueprintReadWrite)
	FVector PlayerScale;
	UPROPERTY(BlueprintReadWrite)
	FRotator PlayerRotator;
	UPROPERTY(BlueprintReadWrite)
	FColor PlayerColor;
	
	UPROPERTY(BlueprintReadWrite)
	int32 PlayerCoin;
};

USTRUCT(BlueprintType)
struct FActorSaveData {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite)
	FName ActorName;
	UPROPERTY(BlueprintReadWrite)
	FVector ActorLocation;
	UPROPERTY(BlueprintReadWrite)
	FVector ActorScale;
	UPROPERTY(BlueprintReadWrite)
	FRotator ActorRotator;
	UPROPERTY(BlueprintReadWrite)
	FVector ActorSpeed;
	UPROPERTY(BlueprintReadWrite)
	bool bIsActive;
	UPROPERTY(BlueprintReadWrite)
	UMaterial* ActorMaterial;
};


UCLASS()
class PLATFORMGAME_API UCustomSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	FPlayerSaveData PlayerSaveData;
	UPROPERTY(BlueprintReadWrite)
	TArray<FActorSaveData> ActorsSaveData;
	//UPROPERTY(BlueprintReadWrite)
	//FPawnSaveData PawnSaveData;
		
	UCustomSaveGame();
};
