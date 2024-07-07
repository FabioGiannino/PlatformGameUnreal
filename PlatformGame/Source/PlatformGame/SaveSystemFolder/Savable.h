#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Savable.generated.h"

UINTERFACE()
class USavable : public UInterface
{
	GENERATED_BODY()
};

class PLATFORMGAME_API ISavable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "SaveGame")
	FVector GetSaveLocation() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "SaveGame")
	UMaterial* GetSaveMaterial() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "SaveGame")
	void LoadMaterialFromSave(UMaterial* Material);
};
