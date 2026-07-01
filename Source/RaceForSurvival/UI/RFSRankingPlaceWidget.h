// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RFSRankingPlaceWidget.generated.h"

UCLASS()
class RACEFORSURVIVAL_API URFSRankingPlaceWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void RankingPlaceSetup(int32 Rank, const FString& PlayerName, float Points, FGuid PlayerID, bool bIsCurrentPlayer);

protected:
	UFUNCTION()
	void OnPlayerNameCommitted(const FText& Text, ETextCommit::Type CommitType);

	void SetupTextBlock(class UTextBlock* TextBlock, const FText& Text, bool bIsCurrentPlayer);

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TBRank;

	UPROPERTY(meta = (BindWidget))
	class UEditableText* ETPlayerName;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TBPoints;

private:
	FGuid CurrentPlayerID;
};
