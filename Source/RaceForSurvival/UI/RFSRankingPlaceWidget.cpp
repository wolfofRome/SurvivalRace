// Fill out your copyright notice in the Description page of Project Settings.


#include "RFSRankingPlaceWidget.h"
#include "Components/TextBlock.h"
#include "Components/EditableText.h"
#include "RaceForSurvival/Game/RFSGameInstance.h"

void URFSRankingPlaceWidget::RankingPlaceSetup(int32 Rank, const FString& PlayerName, float Points, FGuid PlayerID, bool bIsCurrentPlayer)
{
    SetupTextBlock(TBRank, FText::AsNumber(Rank), bIsCurrentPlayer);
    SetupTextBlock(TBPoints, FText::AsNumber(Points), bIsCurrentPlayer);

    if (!ETPlayerName)
    {
        return;
    }

    if (bIsCurrentPlayer)
    {
        CurrentPlayerID = PlayerID;

        ETPlayerName->SetHintText(FText::FromString("Enter name"));
        ETPlayerName->SetText(FText::GetEmpty());
        ETPlayerName->SetIsReadOnly(false);
        ETPlayerName->OnTextCommitted.AddDynamic(this, &URFSRankingPlaceWidget::OnPlayerNameCommitted);

        FEditableTextStyle& TextStyle = ETPlayerName->WidgetStyle;
        TextStyle.SetColorAndOpacity(FSlateColor(FLinearColor::Yellow));
    }
    else
    {
        ETPlayerName->SetText(FText::FromString(PlayerName));
        ETPlayerName->SetIsReadOnly(true);

        FEditableTextStyle& TextStyle = ETPlayerName->WidgetStyle;
        TextStyle.SetColorAndOpacity(FSlateColor(FLinearColor::White));
    }
}

void URFSRankingPlaceWidget::OnPlayerNameCommitted(const FText& Text, ETextCommit::Type CommitType)
{
    if (CommitType == ETextCommit::OnEnter || CommitType == ETextCommit::OnUserMovedFocus)
    {
        URFSGameInstance* GameInstance = Cast<URFSGameInstance>(GetWorld()->GetGameInstance());
        if (GameInstance)
        {
            FString NewName = Text.ToString();
            for (FRFSPlayerData& PlayerData : GameInstance->Ranking)
            {
                if (PlayerData.PlayerID == CurrentPlayerID)
                {
                    PlayerData.PlayerName = NewName;
                    GameInstance->SaveRanking();
                    break;
                }
            }
        }

        ETPlayerName->SetIsReadOnly(true);
    }
}

void URFSRankingPlaceWidget::SetupTextBlock(UTextBlock* TextBlock, const FText& Text, bool bIsCurrentPlayer)
{
    if (TextBlock)
    {
        TextBlock->SetText(Text);
        FSlateColor Color = bIsCurrentPlayer ? FSlateColor(FLinearColor::Yellow) : FSlateColor(FLinearColor::White);
        TextBlock->SetColorAndOpacity(Color);
    }
}
