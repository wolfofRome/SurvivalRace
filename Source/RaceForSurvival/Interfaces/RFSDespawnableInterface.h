// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RFSDespawnableInterface.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDespawnNotify);

UINTERFACE(MinimalAPI)
class URFSDespawnableInterface : public UInterface
{
	GENERATED_BODY()
};

class RACEFORSURVIVAL_API IRFSDespawnableInterface
{
	GENERATED_BODY()

public:
	virtual FDespawnNotify& OnDespawn() = 0;
};
