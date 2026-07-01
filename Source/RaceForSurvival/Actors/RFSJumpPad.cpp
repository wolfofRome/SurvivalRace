// Fill out your copyright notice in the Description page of Project Settings.

#include "RFSJumpPad.h"
#include "GameFramework/Character.h"

// Sets default values
ARFSJumpPad::ARFSJumpPad()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ARFSJumpPad::BeginPlay()
{
	Super::BeginPlay();
}

void ARFSJumpPad::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    Super::OnBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

    if (GetLocalRole() == ROLE_Authority)
    {
        if (OtherActor != nullptr && OtherActor->IsA(ACharacter::StaticClass()))
        {
            if (ACharacter* Character = Cast<ACharacter>(OtherActor))
            {
                ServerInitiateJump(Character);
            }
        }
    }
}

void ARFSJumpPad::ServerInitiateJump_Implementation(ACharacter* Character)
{
    if (Character)
    {
        FVector LaunchVelocity = JumpDirection * JumpForce;
        Character->LaunchCharacter(LaunchVelocity, true, true);
    }
}

bool ARFSJumpPad::ServerInitiateJump_Validate(ACharacter* Character)
{
    return Character != nullptr;
}
