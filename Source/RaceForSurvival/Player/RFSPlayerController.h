// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RFSPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class RACEFORSURVIVAL_API ARFSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void CreateHUD();

	class URFSHUDWidget* GetHUD();
	class URFSRankingWidget* GetRanking();

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerCreateRanking();
	void ServerCreateRanking_Implementation();
	bool ServerCreateRanking_Validate();

	UFUNCTION(NetMulticast, Reliable)
	void ClientCreateRanking();
	void ClientCreateRanking_Implementation();

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RFS|UI")
	TSubclassOf<class URFSHUDWidget> UIHUDWidgetClass;

	UPROPERTY(BlueprintReadWrite, Category = "RFS|UI")
	URFSHUDWidget* UIHUDWidget;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RFS|UI")
	TSubclassOf<class URFSRankingWidget> UIRankingWidgetClass;

	UPROPERTY(BlueprintReadWrite, Category = "RFS|UI")
	URFSRankingWidget* UIRankingWidget;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RFS|Audio")
	class USoundCue* MusicSoundCue;

	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;

	virtual void OnRep_PlayerState() override;

	void CreateRanking();

	UFUNCTION(Client, Reliable)
	void ClientPlayMusic(USoundCue* MusicCue);
	void ClientPlayMusic_Implementation(USoundCue* MusicCue);
};
