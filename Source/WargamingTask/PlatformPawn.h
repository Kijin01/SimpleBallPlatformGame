// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include <Runtime/Engine/Classes/Components/BoxComponent.h>
#include "PlatformPawn.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBallCollision);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUpdatePlayerScore);

UCLASS()
class WARGAMINGTASK_API APlatformPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlatformPawn();

	UPROPERTY(BlueprintReadWrite, Category = LevelBlueprint)
	UBoxComponent* BoxCollider;

	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
	FBallCollision BallScored;

	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
	FUpdatePlayerScore UpdatePlayerScore;

	UFUNCTION(BlueprintCallable, Category = LevelBlueprint)
	int GetPlayerPoints();

	UFUNCTION()
	void SetPlayerPoints(int points);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:

	//INPUT FUNCTIONS

	UFUNCTION()
		void TiltPitch(float valueF);

	UFUNCTION()
		void TiltRoll(float valueF);

	UPROPERTY()
		int PlayerPoints = 2;
};
