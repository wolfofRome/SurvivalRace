// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "RFSAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class RACEFORSURVIVAL_API URFSAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	bool bStartupEffectsApplied = false;
};
