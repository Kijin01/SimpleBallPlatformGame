// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlatformPawn.h"
#include "BallActor.h"
#include "ScoreWidget.generated.h"


class UTextBlock;

UCLASS()
class WARGAMINGTASK_API UScoreWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION()
	void UpdatePlayerScore();

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerScoreBox;

	UPROPERTY(BlueprintReadWrite, Category = LevelBlueprint)
	APlatformPawn* platform;

	UPROPERTY(BlueprintReadWrite, Category = LevelBlueprint)
	ABallActor* ball;

protected:

	virtual void NativeOnInitialized() override;
	
};
