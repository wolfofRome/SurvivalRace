// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "GameplayTagContainer.h"
#include "RFSPlayerState.generated.h"

UCLASS()
class RACEFORSURVIVAL_API ARFSPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ARFSPlayerState();

	class UAbilitySystemComponent* GetAbilitySystemComponent() const;

	class URFSAttributeSetBase* GetAttributeSetBase() const;

	UFUNCTION(BlueprintCallable, Category = "PlayerState")
	bool IsAlive() const;
	
	UFUNCTION(BlueprintCallable, Category = "PlayerState|Attributes")
	float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = "PlayerState|Attributes")
	float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable, Category = "PlayerState|Attributes")
	float GetHealthDamageRate() const;

	UFUNCTION(BlueprintCallable, Category = "PlayerState|Attributes")
	float GetPoints() const;

	UFUNCTION(BlueprintCallable, Category = "PlayerState|Attributes")
	float GetPointsIncreaseRate() const;

	UFUNCTION(BlueprintCallable, Category = "PlayerState|Attributes")
	float GetTimeElapsed() const;

protected:
	UPROPERTY()
	class URFSAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY()
	class URFSAttributeSetBase* AttributeSetBase;

	FGameplayTag DeadTag;

	FDelegateHandle HealthChangedDelegateHandle;
	FDelegateHandle MaxHealthChangedDelegateHandle;
	FDelegateHandle HealthDamageRateChangedDelegateHandle;
	FDelegateHandle PointsChangedDelegateHandle;
	FDelegateHandle PointsIncreaseRateChangedDelegateHandle;
	FDelegateHandle TimeElapsedChangedDelegateHandle;

	virtual void BeginPlay() override;

	virtual void HealthChanged(const FOnAttributeChangeData& Data);
	virtual void MaxHealthChanged(const FOnAttributeChangeData& Data);
	virtual void HealthDamageRateChanged(const FOnAttributeChangeData& Data);
	virtual void PointsChanged(const FOnAttributeChangeData& Data);
	virtual void PointsIncreaseRateChanged(const FOnAttributeChangeData& Data);
	virtual void TimeElapsedChanged(const FOnAttributeChangeData& Data);
};
