// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RFSSpawnManager.generated.h"

/**
 * 
 */
UCLASS()
class RACEFORSURVIVAL_API ARFSSpawnManager : public AActor
{
	GENERATED_BODY()
	
public:
    ARFSSpawnManager();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
    virtual void BeginPlay() override;

public:
    UFUNCTION(Server, Reliable)
    void ServerSpawnObject();
    void ServerSpawnObject_Implementation();

    UFUNCTION(Server, Reliable)
    void ServerDestroySpawnedObject();
    void ServerDestroySpawnedObject_Implementation();

    FTimerHandle LifeSpanTimer;

    UPROPERTY(EditAnywhere, Category = "RFS|Spawn Settings")
    TArray<AActor*> SpawnAreas;

    UPROPERTY(EditAnywhere, Category = "RFS|Spawn Settings")
    TSubclassOf<AActor> ObjectClassToSpawn;

    UPROPERTY(EditAnywhere, Category = "RFS|Spawn Settings")
    float LifeSpan = 6.f;

    UPROPERTY(Replicated)
    AActor* SpawnedObject;

    UPROPERTY(Replicated)
    AActor* LastSpawnArea;

private:
    AActor* GetRandomSpawnArea();
};
