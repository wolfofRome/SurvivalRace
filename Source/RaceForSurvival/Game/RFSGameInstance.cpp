// Fill out your copyright notice in the Description page of Project Settings.


#include "RFSGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "RaceForSurvival/Game/RFSSaveGame.h"

void URFSGameInstance::Init()
{
    Super::Init();

    LoadRanking();
}

void URFSGameInstance::SavePlayerData(const FRFSPlayerData& NewData)
{
    Ranking.Add(NewData);
    Ranking.Sort([](const FRFSPlayerData& A, const FRFSPlayerData& B) {
        return A.Points > B.Points;
        });

    if (Ranking.Num() > 10)
    {
        Ranking.SetNum(10);
    }

    SaveRanking();
}

void URFSGameInstance::SaveRanking()
{
    URFSSaveGame* SaveGame = Cast<URFSSaveGame>(UGameplayStatics::CreateSaveGameObject(URFSSaveGame::StaticClass()));

    SaveGame->Ranking = Ranking;

    UGameplayStatics::SaveGameToSlot(SaveGame, TEXT("RankingSaveSlot"), 0);
}

void URFSGameInstance::LoadRanking()
{
    URFSSaveGame* LoadGame = Cast<URFSSaveGame>(UGameplayStatics::CreateSaveGameObject(URFSSaveGame::StaticClass()));

    LoadGame = Cast<URFSSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("RankingSaveSlot"), 0));
    if (LoadGame)
    {
        Ranking = LoadGame->Ranking;
    }
}
