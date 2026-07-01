// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RaceForSurvival/Actors/RFSBaseActor.h"
#include "Components/StaticMeshComponent.h"
#include "RFSJumpPad.generated.h"

UCLASS()
class RACEFORSURVIVAL_API ARFSJumpPad : public ARFSBaseActor
{
	GENERATED_BODY()
	
public:	
	ARFSJumpPad();

protected:
	virtual void BeginPlay() override;

    virtual void OnBeginOverlap(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

    UFUNCTION(Server, Reliable, WithValidation)
    void ServerInitiateJump(ACharacter* Character);
    void ServerInitiateJump_Implementation(ACharacter* Character);
    bool ServerInitiateJump_Validate(ACharacter* Character);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RFS|JumpSettings")
    FVector JumpDirection = FVector(0.f, 0.f, 1.f);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RFS|JumpSettings")
    float JumpForce = 1800.f;
};
