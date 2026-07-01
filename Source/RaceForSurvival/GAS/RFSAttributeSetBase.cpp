// Fill out your copyright notice in the Description page of Project Settings.


#include "RFSAttributeSetBase.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

URFSAttributeSetBase::URFSAttributeSetBase()
{
}

void URFSAttributeSetBase::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	// If a Max value changes, adjust current to keep Current % of Current to Max
	if (Attribute == GetMaxHealthAttribute())
	{
		AdjustAttributeForMaxChange(Health, MaxHealth, NewValue, GetHealthAttribute());
	}
}

void URFSAttributeSetBase::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
	}
}

void URFSAttributeSetBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(URFSAttributeSetBase, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(URFSAttributeSetBase, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(URFSAttributeSetBase, HealthDamageRate, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(URFSAttributeSetBase, Points, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(URFSAttributeSetBase, PointsIncreaseRate, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(URFSAttributeSetBase, TimeElapsed, COND_None, REPNOTIFY_Always);
}

void URFSAttributeSetBase::AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty)
{
	UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
	const float CurrentMaxValue = MaxAttribute.GetCurrentValue();
	if (!FMath::IsNearlyEqual(CurrentMaxValue, NewMaxValue) && AbilityComp)
	{
		// Change current value to maintain the current Val / Max percent
		const float CurrentValue = AffectedAttribute.GetCurrentValue();
		float NewDelta = (CurrentMaxValue > 0.f) ? (CurrentValue * NewMaxValue / CurrentMaxValue) - CurrentValue : NewMaxValue;

		AbilityComp->ApplyModToAttributeUnsafe(AffectedAttributeProperty, EGameplayModOp::Additive, NewDelta);
	}
}

void URFSAttributeSetBase::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URFSAttributeSetBase, Health, OldHealth);
}

void URFSAttributeSetBase::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URFSAttributeSetBase, MaxHealth, OldMaxHealth);
}

void URFSAttributeSetBase::OnRep_HealthDamageRate(const FGameplayAttributeData& OldHealthDamageRate)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URFSAttributeSetBase, HealthDamageRate, OldHealthDamageRate);
}

void URFSAttributeSetBase::OnRep_Points(const FGameplayAttributeData& OldPoints)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URFSAttributeSetBase, Points, OldPoints);
}

void URFSAttributeSetBase::OnRep_PointsIncreaseRate(const FGameplayAttributeData& OldPointsIncreaseRate)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URFSAttributeSetBase, PointsIncreaseRate, OldPointsIncreaseRate);
}

void URFSAttributeSetBase::OnRep_TimeElapsed(const FGameplayAttributeData& OldTimeElapsed)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URFSAttributeSetBase, TimeElapsed, OldTimeElapsed);
}
