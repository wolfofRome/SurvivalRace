// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RFSRankingWidget.generated.h"

/**
 * 
 */
UCLASS()
class RACEFORSURVIVAL_API URFSRankingWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetupRanking(float Points);

protected:
	virtual void NativeOnInitialized() override;

	UFUNCTION()
	void ReturnButtonClicked();

	UFUNCTION()
	void OnDestroySession(bool bWasSuccessful);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "RFS|UI")
	TSubclassOf<class URFSRankingPlaceWidget> RankingPlaceWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "RFS|UI")
	FString MainMenuPath = "Game/RaceForSurvival/Maps/Level_MainMenu";

private:

	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* RankingVerticalBox;

	UPROPERTY(meta = (BindWidget))
	class UButton* ReturnButton;

	UPROPERTY()
	class UMultiplayerSessionsSubsystem* MultiplayerSessionsSubsystem;
};
