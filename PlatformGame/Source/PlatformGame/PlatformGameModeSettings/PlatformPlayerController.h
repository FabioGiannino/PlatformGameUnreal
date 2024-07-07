#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlatformPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCollectedCoins, int32,AmountParam);
UCLASS()
class PLATFORMGAME_API APlatformPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collectibles")
	int32 CollectedCoins;
	
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FCollectedCoins OnPickUpCoin;
	
	UFUNCTION(BlueprintCallable, Category = "Collectibles")
	void AddCoin();
	UFUNCTION(BlueprintCallable)
	void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
	void TriggerEvents();
};
