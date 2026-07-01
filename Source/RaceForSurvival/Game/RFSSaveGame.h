// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "RaceForSurvival/Game/RFSGameInstance.h"
#include "RFSSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class RACEFORSURVIVAL_API URFSSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category = "RFS|Ranking")
	TArray<FRFSPlayerData> Ranking;
};
