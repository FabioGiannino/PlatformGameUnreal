// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "PlatformGame/SaveSystemFolder/Savable.h"
#include "Ball.generated.h"

UCLASS()
class PLATFORMGAME_API ABall : public AStaticMeshActor,public ISavable
{
	GENERATED_BODY()

public:
	ABall();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
