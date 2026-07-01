// Fill out your copyright notice in the Description page of Project Settings.


#include "RFSMedKit.h"
#include "Components/BoxComponent.h"
#include "RaceForSurvival/Character/RaceForSurvivalCharacter.h"
#include "AbilitySystemComponent.h"

ARFSMedKit::ARFSMedKit()
{
	PrimaryActorTick.bCanEverTick = true;

    MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ARFSMedKit::BeginPlay()
{
	Super::BeginPlay();

    RotationRandomSpeed = FMath::RandRange(-RotationSpeedRange, RotationSpeedRange);
}

void ARFSMedKit::UpdateRotationAndMovement()
{
    FRotator DeltaRotation(RotationRandomSpeed, 0.0f, 0.0f);
    MeshComponent->AddLocalRotation(DeltaRotation);
}

void ARFSMedKit::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    UpdateRotationAndMovement();
}

void ARFSMedKit::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    Super::OnBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

    if (GetLocalRole() == ROLE_Authority)
    {
        if (OtherActor != nullptr && OtherActor->IsA(ARaceForSurvivalCharacter::StaticClass()))
        {
            if (ARaceForSurvivalCharacter* Character = Cast<ARaceForSurvivalCharacter>(OtherActor))
            {
                ServerInitiateHeal(Character);
            }
        }
    }
}

void ARFSMedKit::ServerInitiateHeal_Implementation(ARaceForSurvivalCharacter* Character)
{
    if (Character)
    {
        UAbilitySystemComponent* AbilitySystem = Character->GetAbilitySystemComponent();
        if (!AbilitySystem || !AbilitySystem->IsValidLowLevel())
        {
            return;
        }

        FGameplayEffectContextHandle EffectContext = AbilitySystem->MakeEffectContext();
        EffectContext.AddSourceObject(this);

        FGameplayEffectSpecHandle EffectSpecHandle = AbilitySystem->MakeOutgoingSpec(HealGameplayEffect, 1, EffectContext);
        if (EffectSpecHandle.IsValid())
        {
            FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystem->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(), AbilitySystem);
            OnDespawn().Broadcast();
        }
    }
}

bool ARFSMedKit::ServerInitiateHeal_Validate(ARaceForSurvivalCharacter* Character)
{
    return Character != nullptr;
}
