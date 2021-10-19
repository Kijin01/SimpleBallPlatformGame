// Fill out your copyright notice in the Description page of Project Settings.


#include "BallActor.h"

// Sets default values
ABallActor::ABallActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABallActor::BeginPlay()
{
	Super::BeginPlay();
	//Get reference to the player pawn, which is our platform
	platform = Cast<APlatformPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
	
}

// Called every frame
void ABallActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (platform != nullptr) {	//Light check for platform
		if (GetActorLocation().Z < (platform->GetActorLocation().Z - 2000.0f)) {
			BallOutsideBounds.Broadcast();
		}
	}	

}

