// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include <Runtime\Engine\Classes\Kismet\GameplayStatics.h>
#include "PlatformPawn.h"
#include "BallActor.h"
#include <Runtime/Engine/Classes/Components/StaticMeshComponent.h>
#include "PlatformLevelScript.generated.h"

/**
 * 
 */




UCLASS()
class WARGAMINGTASK_API APlatformLevelScript : public ALevelScriptActor
{
	GENERATED_BODY()

public:

	APlatformLevelScript();

	UFUNCTION()
	void WhenBallScored();

	UFUNCTION()
	void WhenBallOutOfBounds();

	UPROPERTY(BlueprintReadWrite, Category = LevelBlueprint)
	FVector ballStartingOffset = FVector(-347.0f, 305.0f, 1450.0f);

	UPROPERTY(BlueprintReadWrite, Category = LevelBlueprint)
	ABallActor* ball;

	UPROPERTY(BlueprintReadWrite, Category = LevelBlueprint)
	UStaticMeshComponent* ballMesh;

	UPROPERTY(BlueprintReadWrite, Category = LevelBlueprint)
	APlatformPawn* platform;


protected:
	//Begin Play
	virtual void BeginPlay();

public:
	//Tick
	virtual void Tick(float DeltaTime);
	
};
