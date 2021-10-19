// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreWidget.h"
#include <Runtime/UMG/Public/Components/TextBlock.h>
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

void UScoreWidget::NativeOnInitialized()
{

	//Get reference to the player pawn, which is our platform
	platform = Cast<APlatformPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());

	//Initialize the textbox
	double startingScore = platform->GetPlayerPoints();
	startingScore /= 2;
	PlayerScoreBox->SetText(FText::FromString(FString::SanitizeFloat(startingScore, 0)));
	

	//Get the reference to the ball actor in the scene
	TArray<AActor*> BallActors{};
	UGameplayStatics::GetAllActorsWithTag(this, "Ball", BallActors);
	for (const auto& BallActor : BallActors)
	{
		ball = Cast<ABallActor>(BallActor);
	}

	if (platform != nullptr && ball != nullptr) {	
		//Bind the broadcasted event to the UpdatePlayerScore function
		platform->UpdatePlayerScore.AddDynamic(this, &UScoreWidget::UpdatePlayerScore);	
	}
}

void UScoreWidget::UpdatePlayerScore() {

	double formatted_score;

	if (platform->GetPlayerPoints() > 0) {
		formatted_score = platform->GetPlayerPoints();
		formatted_score /= 2;
	}

	PlayerScoreBox->SetText(FText::FromString(FString::SanitizeFloat(formatted_score, 0)));

	//PlayerScoreBox->SetText(FText::AsNumber(platform->GetPlayerPoints()));

	
}
