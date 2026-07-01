// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RaceForSurvival/Actors/RFSBaseActor.h"
#include "RaceForSurvival/Interfaces/RFSDespawnableInterface.h"
#include "RFSMedKit.generated.h"

class ARaceForSurvivalCharacter;

UCLASS()
class RACEFORSURVIVAL_API ARFSMedKit : public ARFSBaseActor, public IRFSDespawnableInterface
{
	GENERATED_BODY()
	
public:	
	ARFSMedKit();

    virtual void Tick(float DeltaTime) override;

protected:
    virtual void BeginPlay() override;

    void UpdateRotationAndMovement();

    virtual void OnBeginOverlap(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

    UFUNCTION(Server, Reliable, WithValidation)
    void ServerInitiateHeal(ARaceForSurvivalCharacter* Character);
    void ServerInitiateHeal_Implementation(ARaceForSurvivalCharacter* Character);
    bool ServerInitiateHeal_Validate(ARaceForSurvivalCharacter* Character);

    virtual FDespawnNotify& OnDespawn() override { return DespawnNotify; }

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RFS|GameplayEffects")
    TSubclassOf<class UGameplayEffect> HealGameplayEffect;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RFS|Rotation")
    float RotationSpeedRange = 4.0f;

private:
    FDespawnNotify DespawnNotify;

    float RotationRandomSpeed = 4.0f;
};
