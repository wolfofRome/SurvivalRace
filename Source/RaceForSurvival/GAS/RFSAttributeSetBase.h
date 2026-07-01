// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "RFSAttributeSetBase.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class RACEFORSURVIVAL_API URFSAttributeSetBase : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	URFSAttributeSetBase();

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(URFSAttributeSetBase, Health)

	UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(URFSAttributeSetBase, MaxHealth)

	UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_HealthDamageRate)
	FGameplayAttributeData HealthDamageRate;
	ATTRIBUTE_ACCESSORS(URFSAttributeSetBase, HealthDamageRate)

	UPROPERTY(BlueprintReadOnly, Category = "Points", ReplicatedUsing = OnRep_Points)
	FGameplayAttributeData Points;
	ATTRIBUTE_ACCESSORS(URFSAttributeSetBase, Points)

	UPROPERTY(BlueprintReadOnly, Category = "Points", ReplicatedUsing = OnRep_PointsIncreaseRate)
	FGameplayAttributeData PointsIncreaseRate;
	ATTRIBUTE_ACCESSORS(URFSAttributeSetBase, PointsIncreaseRate)

	UPROPERTY(BlueprintReadOnly, Category = "Time", ReplicatedUsing = OnRep_TimeElapsed)
	FGameplayAttributeData TimeElapsed;
	ATTRIBUTE_ACCESSORS(URFSAttributeSetBase, TimeElapsed)

protected:
	// Helper function to proportionally adjust the value of an attribute when it's associated max attribute changes.
	void AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty);

	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);

	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);

	UFUNCTION()
	virtual void OnRep_HealthDamageRate(const FGameplayAttributeData& OldHealthDamageRate);

	UFUNCTION()
	virtual void OnRep_Points(const FGameplayAttributeData& OldPoints);

	UFUNCTION()
	virtual void OnRep_PointsIncreaseRate(const FGameplayAttributeData& OldPointsIncreaseRate);

	UFUNCTION()
	virtual void OnRep_TimeElapsed(const FGameplayAttributeData& OldTimeElapsed);
};
