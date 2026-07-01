// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "RFSGameInstance.generated.h"

USTRUCT(BlueprintType)
struct FRFSPlayerData
{
    GENERATED_BODY()

    FRFSPlayerData() : Points(0.0f), PlayerID(FGuid::NewGuid()) {}

    FRFSPlayerData(const FString& InPlayerName, float InPoints, const FGuid& InPlayerID)
        : PlayerName(InPlayerName), Points(InPoints), PlayerID(InPlayerID) {}

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString PlayerName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Points;

    UPROPERTY()
    FGuid PlayerID;
};

UCLASS()
class RACEFORSURVIVAL_API URFSGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
    virtual void Init() override;

    UPROPERTY(BlueprintReadWrite, Category = "RFS|Ranking")
    TArray<FRFSPlayerData> Ranking;

    void SavePlayerData(const FRFSPlayerData& NewData);

    void SaveRanking();

    void LoadRanking();
};
