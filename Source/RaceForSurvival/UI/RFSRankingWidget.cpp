// Fill out your copyright notice in the Description page of Project Settings.


#include "RFSRankingWidget.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/Button.h"
#include "RaceForSurvival/UI/RFSRankingPlaceWidget.h"
#include "RaceForSurvival/Game/RFSGameInstance.h"
#include "MultiplayerSessionsSubsystem.h"

void URFSRankingWidget::SetupRanking(float Points)
{
	if (!RankingVerticalBox || !RankingPlaceWidgetClass)
	{
		return;
	}

	URFSGameInstance* GameInstance = Cast<URFSGameInstance>(GetGameInstance());
	if (!GameInstance)
	{
		return;
	}

	if (APlayerController* PlayerController = Cast<APlayerController>(GetOwningPlayer()))
	{
		FInputModeUIOnly InputModeData;
		InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		PlayerController->SetInputMode(InputModeData);
		PlayerController->SetShowMouseCursor(true);
	}

	FGuid CurrentPlayerID = FGuid::NewGuid();

	GameInstance->SavePlayerData(FRFSPlayerData(TEXT("Player"), Points, CurrentPlayerID));

	RankingVerticalBox->ClearChildren();

	int Rank = 1;
	for (const FRFSPlayerData& PlayerData : GameInstance->Ranking)
	{
		if (URFSRankingPlaceWidget* RankingPlaceWidget = CreateWidget<URFSRankingPlaceWidget>(GetOwningPlayer(), RankingPlaceWidgetClass))
		{
			bool bIsCurrentPlayer = (PlayerData.PlayerID == CurrentPlayerID);
			RankingPlaceWidget->RankingPlaceSetup(Rank, PlayerData.PlayerName, PlayerData.Points, PlayerData.PlayerID, bIsCurrentPlayer);
			Rank++;

			UVerticalBoxSlot* VerticalBoxSlot = RankingVerticalBox->AddChildToVerticalBox(RankingPlaceWidget);
			if (VerticalBoxSlot)
			{
				VerticalBoxSlot->SetHorizontalAlignment(HAlign_Fill);
				FMargin SlotPadding;
				SlotPadding.Bottom = 10.f;
				VerticalBoxSlot->SetPadding(SlotPadding);
			}
		}
	}

	MultiplayerSessionsSubsystem = GameInstance->GetSubsystem<UMultiplayerSessionsSubsystem>();
	if (MultiplayerSessionsSubsystem)
	{
		MultiplayerSessionsSubsystem->MultiplayerOnDestroySessionComplete.AddDynamic(this, &URFSRankingWidget::OnDestroySession);
	}
}

void URFSRankingWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (ReturnButton)
	{
		ReturnButton->OnClicked.AddDynamic(this, &URFSRankingWidget::ReturnButtonClicked);
	}
}

void URFSRankingWidget::ReturnButtonClicked()
{
	if (MultiplayerSessionsSubsystem)
	{
		MultiplayerSessionsSubsystem->DestroySession();
	}
}

void URFSRankingWidget::OnDestroySession(bool bWasSuccessful)
{
	APlayerController* PlayerController = Cast<APlayerController>(GetOwningPlayer());
	if (PlayerController)
	{
		PlayerController->ClientTravel(MainMenuPath, ETravelType::TRAVEL_Absolute);
	}
}
