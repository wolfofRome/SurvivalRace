// Fill out your copyright notice in the Description page of Project Settings.


#include "RFSIncreaseDifficultyExecCalculation.h"
#include "RaceForSurvival/GAS/RFSAttributeSetBase.h"

struct RFSStatistics
{
    DECLARE_ATTRIBUTE_CAPTUREDEF(TimeElapsed);
	DECLARE_ATTRIBUTE_CAPTUREDEF(PointsIncreaseRate);
    DECLARE_ATTRIBUTE_CAPTUREDEF(HealthDamageRate);

    RFSStatistics()
	{
        DEFINE_ATTRIBUTE_CAPTUREDEF(URFSAttributeSetBase, TimeElapsed, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(URFSAttributeSetBase, PointsIncreaseRate, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(URFSAttributeSetBase, HealthDamageRate, Target, false);
	}
};

static const RFSStatistics& Statistics()
{
	static RFSStatistics Statistics;
	return Statistics;
}

URFSIncreaseDifficultyExecCalculation::URFSIncreaseDifficultyExecCalculation()
{
    RelevantAttributesToCapture.Add(Statistics().TimeElapsedDef);
	RelevantAttributesToCapture.Add(Statistics().PointsIncreaseRateDef);
    RelevantAttributesToCapture.Add(Statistics().HealthDamageRateDef);
}

void URFSIncreaseDifficultyExecCalculation::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
    //This is where the difficulty of the game changes, these variables can be added to Attributes to provide difficulty changes in Blueprints
    float CurrentTimeElapsed = 0.f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(Statistics().TimeElapsedDef, FAggregatorEvaluateParameters(), CurrentTimeElapsed);

    int PeriodsElapsed = CurrentTimeElapsed / 50;
    float IncrementPointsPerPeriod = 10.f;
    float IncrementHealthDamagePerPeriod = -1.f;

    float NewPointsIncreaseRate = IncrementPointsPerPeriod + IncrementPointsPerPeriod * PeriodsElapsed;
    float NewHealthDamageRate = IncrementHealthDamagePerPeriod + IncrementHealthDamagePerPeriod * PeriodsElapsed;

    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(Statistics().PointsIncreaseRateProperty, EGameplayModOp::Override, NewPointsIncreaseRate));

    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(Statistics().HealthDamageRateProperty, EGameplayModOp::Override, NewHealthDamageRate));
}

