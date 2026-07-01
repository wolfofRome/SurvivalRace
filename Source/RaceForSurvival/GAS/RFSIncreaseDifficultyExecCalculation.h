// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "RFSIncreaseDifficultyExecCalculation.generated.h"

/**
 * 
 */
UCLASS()
class RACEFORSURVIVAL_API URFSIncreaseDifficultyExecCalculation : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

	URFSIncreaseDifficultyExecCalculation();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
