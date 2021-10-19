// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformPawn.h"

// Sets default values
APlatformPawn::APlatformPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void APlatformPawn::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Check that it was the other actor that triggered the event and also check that it is not this current actor itself
	if (OtherActor != nullptr && (OtherActor != this) && OtherComp != nullptr) {	
		BallScored.Broadcast();		
	}
}


int APlatformPawn::GetPlayerPoints()
{
	return this->PlayerPoints;
}

void APlatformPawn::SetPlayerPoints(int points)
{
	this->PlayerPoints = points;
}

// Called when the game starts or when spawned
void APlatformPawn::BeginPlay()
{
	Super::BeginPlay();

	//PlayerPoints = 1.0; //Player starts with 1 point

	BoxCollider = this->FindComponentByClass<UBoxComponent>();

	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &APlatformPawn::OnBoxBeginOverlap); //Bind the OnComponentBeginOverlap event to the OnBoxBeginOverlap function
	
}

// Called every frame
void APlatformPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlatformPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//W and S
	InputComponent->BindAxis(TEXT("TiltPitch"), this, &APlatformPawn::TiltPitch);

	//A and D
	InputComponent->BindAxis(TEXT("TiltRoll"), this, &APlatformPawn::TiltRoll);

	

}


//Define HoldKey functions

//W and S
void APlatformPawn::TiltPitch(float valueF) {
	if (GetActorRotation().Pitch + valueF < 89.0f && GetActorRotation().Pitch + valueF > -89.0f) {
		SetActorRelativeRotation(GetActorRotation().Add(valueF, 0.0f, 0.0f));
	}
}


//A and D
void APlatformPawn::TiltRoll(float valueF) {
	if (GetActorRotation().Roll + valueF < 89.0f && GetActorRotation().Roll + valueF > -89.0f) {
		SetActorRelativeRotation(GetActorRotation().Add(0.0f, 0.0f, valueF));
	}
}



