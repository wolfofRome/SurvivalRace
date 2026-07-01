// Fill out your copyright notice in the Description page of Project Settings.


#include "RFSPlayerState.h"
#include "RaceForSurvival/GAS/RFSAttributeSetBase.h"
#include "RaceForSurvival/GAS/RFSAbilitySystemComponent.h"
#include "RFSPlayerController.h"
#include "RaceForSurvival/UI/RFSHUDWidget.h"
#include "RaceForSurvival/Character/RaceForSurvivalCharacter.h"

ARFSPlayerState::ARFSPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<URFSAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);

	// Mixed mode means we only are replicated the GEs to ourself, not the GEs to simulated proxies. If another GDPlayerState (Hero) receives a GE,
	// we won't be told about it by the Server. Attributes, GameplayTags, and GameplayCues will still replicate to us.
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	// Create the attribute set, this replicates by default
	AttributeSetBase = CreateDefaultSubobject<URFSAttributeSetBase>(TEXT("AttributeSetBase"));

	// Set PlayerState's NetUpdateFrequency to the same as the Character.
	// Default is very low for PlayerStates and introduces perceived lag in the ability system.
	NetUpdateFrequency = 100.0f;

	DeadTag = FGameplayTag::RequestGameplayTag(FName("State.Dead"));
}

UAbilitySystemComponent* ARFSPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

URFSAttributeSetBase* ARFSPlayerState::GetAttributeSetBase() const
{
	return AttributeSetBase;
}

bool ARFSPlayerState::IsAlive() const
{
	return GetHealth() > 0.0f;
}

float ARFSPlayerState::GetHealth() const
{
	return AttributeSetBase->GetHealth();
}

float ARFSPlayerState::GetMaxHealth() const
{
	return AttributeSetBase->GetMaxHealth();
}

float ARFSPlayerState::GetHealthDamageRate() const
{
	return AttributeSetBase->GetHealthDamageRate();
}

float ARFSPlayerState::GetPoints() const
{
	return AttributeSetBase->GetPoints();
}

float ARFSPlayerState::GetPointsIncreaseRate() const
{
	return AttributeSetBase->GetPointsIncreaseRate();
}

float ARFSPlayerState::GetTimeElapsed() const
{
	return AttributeSetBase->GetTimeElapsed();
}

void ARFSPlayerState::BeginPlay()
{
	Super::BeginPlay();

	if (AbilitySystemComponent)
	{
		HealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetHealthAttribute()).AddUObject(this, &ARFSPlayerState::HealthChanged);
		MaxHealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetMaxHealthAttribute()).AddUObject(this, &ARFSPlayerState::MaxHealthChanged);
		HealthDamageRateChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetHealthDamageRateAttribute()).AddUObject(this, &ARFSPlayerState::HealthDamageRateChanged);
		PointsChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetPointsAttribute()).AddUObject(this, &ARFSPlayerState::PointsChanged);
		PointsIncreaseRateChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetPointsIncreaseRateAttribute()).AddUObject(this, &ARFSPlayerState::PointsIncreaseRateChanged);
		TimeElapsedChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetTimeElapsedAttribute()).AddUObject(this, &ARFSPlayerState::TimeElapsedChanged);
	}
}

void ARFSPlayerState::HealthChanged(const FOnAttributeChangeData& Data)
{
	float Health = Data.NewValue;

	ARFSPlayerController* PC = Cast<ARFSPlayerController>(GetOwner());
	if (PC)
	{
		URFSHUDWidget* HUD = PC->GetHUD();
		if (HUD)
		{
			HUD->SetCurrentHealth(Health);
			HUD->SetHealthPercentage(Health / GetMaxHealth());
		}
	}	

	if (!IsAlive() && !AbilitySystemComponent->HasMatchingGameplayTag(DeadTag))
	{
		ARaceForSurvivalCharacter* Player = Cast<ARaceForSurvivalCharacter>(GetPawn());
		if (Player)
		{
			Player->Die();
		}
	}
}

void ARFSPlayerState::MaxHealthChanged(const FOnAttributeChangeData& Data)
{
	float MaxHealth = Data.NewValue;

	ARFSPlayerController* PC = Cast<ARFSPlayerController>(GetOwner());
	if (PC)
	{
		URFSHUDWidget* HUD = PC->GetHUD();
		if (HUD)
		{
			HUD->SetMaxHealth(MaxHealth);
		}
	}

}

void ARFSPlayerState::HealthDamageRateChanged(const FOnAttributeChangeData& Data)
{
}

void ARFSPlayerState::PointsChanged(const FOnAttributeChangeData& Data)
{
	float Points = Data.NewValue;

	ARFSPlayerController* PC = Cast<ARFSPlayerController>(GetOwner());
	if (PC)
	{
		URFSHUDWidget* HUD = PC->GetHUD();
		if (HUD)
		{
			HUD->SetCurrentPoints(Points);
		}
	}
}

void ARFSPlayerState::PointsIncreaseRateChanged(const FOnAttributeChangeData& Data)
{
}

void ARFSPlayerState::TimeElapsedChanged(const FOnAttributeChangeData& Data)
{
}
