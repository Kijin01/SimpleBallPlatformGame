// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlatformPawn.h"
#include "BallActor.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBallOutOfBounds);

UCLASS()
class WARGAMINGTASK_API ABallActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABallActor();

	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
	FBallOutOfBounds BallOutsideBounds;
	
	UPROPERTY(BlueprintReadWrite, Category = LevelBlueprint)
	APlatformPawn* platform;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
