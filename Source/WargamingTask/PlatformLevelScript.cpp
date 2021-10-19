// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformLevelScript.h"

APlatformLevelScript::APlatformLevelScript() {
	PrimaryActorTick.bCanEverTick = true;
}

void APlatformLevelScript::BeginPlay() {

	Super::BeginPlay();


	//PLATFORM
	platform = Cast<APlatformPawn>(GetWorld()->GetFirstPlayerController()->GetPawn()); //Get reference to the player pawn, which is our platform
	platform->BallScored.AddDynamic(this, &APlatformLevelScript::WhenBallScored);	//Bind the broadcasted event to the WhenBallScored function


	//----------------------------------------------------------------------------------------------------------------------------------------------


	//BALL
	//Get the ball actor reference in the scene by tag and casting it to ABallActor class. Expensive operation, but it's fine since it's done only once on BeginPlay
	TArray<AActor*> BallActors{};
	UGameplayStatics::GetAllActorsWithTag(this, "Ball", BallActors);
	for (const auto& BallActor : BallActors)
	{
		ball = Cast<ABallActor>(BallActor);
	}
	//Bind the broadcasted event to the WhenBallOutOfBounds function
	ball->BallOutsideBounds.AddDynamic(this, &APlatformLevelScript::WhenBallOutOfBounds);

	//Get the static mesh component of the ball so we can manipulate its' physics
	ballMesh = ball->FindComponentByClass<UStaticMeshComponent>();	
}

void APlatformLevelScript::WhenBallScored()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "BALL SCORED");
	platform->SetPlayerPoints(platform->GetPlayerPoints() + 2);
	
	platform->UpdatePlayerScore.Broadcast();	//Broadcast the score update event only after the score has been changed

	ballMesh->SetAllPhysicsLinearVelocity(FVector(0.0f, 0.0f, 0.0f));	//Reset ball's linear velocity
	ballMesh->SetAllPhysicsAngularVelocityInRadians(FVector(0.0f, 0.0f, 0.0f));	//Reset ball's angular velocity

	

	ball->SetActorLocation((platform->GetActorLocation() + ballStartingOffset));	//Reset the location of the ball
}

void APlatformLevelScript::WhenBallOutOfBounds()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "BALL OUT OF BOUNDS");
	platform->SetPlayerPoints(platform->GetPlayerPoints() - 1);

	platform->UpdatePlayerScore.Broadcast();	//Broadcast the score update event only after the score has been changed

	ballMesh->SetAllPhysicsLinearVelocity(FVector(0.0f, 0.0f, 0.0f));	//Reset ball's linear velocity
	ballMesh->SetAllPhysicsAngularVelocityInRadians(FVector(0.0f, 0.0f, 0.0f));	//Reset ball's angular velocity

	ball->SetActorLocation((platform->GetActorLocation() + ballStartingOffset));	//Reset the location of the ball
}

void APlatformLevelScript::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (platform->GetPlayerPoints() < 0) {
		UGameplayStatics::OpenLevel(this, "GameOver_Level");
	}	
}

