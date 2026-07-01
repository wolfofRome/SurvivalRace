// Fill out your copyright notice in the Description page of Project Settings.


#include "RFSPlayerController.h"
#include "AbilitySystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "RFSPlayerState.h"
#include "RaceForSurvival/UI/RFSHUDWidget.h"
#include "RaceForSurvival/UI/RFSRankingWidget.h"

void ARFSPlayerController::CreateHUD()
{
	if (UIHUDWidget)
	{
		return;
	}

	if (!UIHUDWidgetClass)
	{
		UE_LOG(LogTemp, Error, TEXT("%s() Missing UIHUDWidgetClass. Please fill in on the Blueprint of the PlayerController."), *FString(__FUNCTION__));
		return;
	}

	ARFSPlayerState* PS = GetPlayerState<ARFSPlayerState>();
	if (!PS)
	{
		return;
	}

	UIHUDWidget = CreateWidget<URFSHUDWidget>(this, UIHUDWidgetClass);
	UIHUDWidget->AddToViewport();

	UIHUDWidget->SetCurrentHealth(PS->GetHealth());
	UIHUDWidget->SetMaxHealth(PS->GetMaxHealth());
	UIHUDWidget->SetHealthPercentage(PS->GetHealth() / FMath::Max<float>(PS->GetMaxHealth(), 1.f));
	UIHUDWidget->SetCurrentPoints(PS->GetPoints());
}

void ARFSPlayerController::CreateRanking()
{
	if (UIRankingWidget)
	{
		return;
	}

	if (!UIRankingWidgetClass)
	{
		UE_LOG(LogTemp, Error, TEXT("%s() Missing UIRankingWidgetClass. Please fill in on the Blueprint of the PlayerController."), *FString(__FUNCTION__));
		return;
	}

	UIRankingWidget = CreateWidget<URFSRankingWidget>(this, UIRankingWidgetClass);
	UIRankingWidget->AddToViewport();

	if (ARFSPlayerState* PS = GetPlayerState<ARFSPlayerState>())
	{
		UIRankingWidget->SetupRanking(PS->GetPoints());
	}
}

URFSHUDWidget* ARFSPlayerController::GetHUD()
{
	return UIHUDWidget;
}

URFSRankingWidget* ARFSPlayerController::GetRanking()
{
	return UIRankingWidget;
}

void ARFSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (MusicSoundCue)
	{
		ClientPlayMusic(MusicSoundCue);
	}
}

void ARFSPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ARFSPlayerState* PS = GetPlayerState<ARFSPlayerState>();
	if (PS)
	{
		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, InPawn);
	}
}

void ARFSPlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// For edge cases where the PlayerState is repped before the Hero is possessed.
	CreateHUD();
}

void ARFSPlayerController::ServerCreateRanking_Implementation()
{
	ClientCreateRanking();
}

bool ARFSPlayerController::ServerCreateRanking_Validate()
{
	return true;
}

void ARFSPlayerController::ClientCreateRanking_Implementation()
{
	if (IsLocalPlayerController())
	{
		CreateRanking();
	}
}

void ARFSPlayerController::ClientPlayMusic_Implementation(USoundCue* MusicCue)
{
	if (MusicCue)
	{
		UGameplayStatics::PlaySound2D(this, MusicCue);
	}
}
