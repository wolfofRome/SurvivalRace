// Fill out your copyright notice in the Description page of Project Settings.


#include "RFSSpawnManager.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Net/UnrealNetwork.h"
#include "RaceForSurvival/Interfaces/RFSDespawnableInterface.h"

ARFSSpawnManager::ARFSSpawnManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ARFSSpawnManager::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME_CONDITION(ARFSSpawnManager, SpawnedObject, COND_None);
    DOREPLIFETIME_CONDITION(ARFSSpawnManager, LastSpawnArea, COND_None);
}

void ARFSSpawnManager::BeginPlay()
{
	Super::BeginPlay();

    if (GetLocalRole() == ROLE_Authority)
    {
        ServerSpawnObject();
    }
}

void ARFSSpawnManager::ServerSpawnObject_Implementation()
{
    if (SpawnedObject != nullptr)
    {
        ServerDestroySpawnedObject();
    }

    AActor* SpawnArea = GetRandomSpawnArea();
    if (SpawnArea)
    {
        FVector Location = FMath::RandPointInBox(SpawnArea->GetComponentsBoundingBox());
        Location = Location + FVector(0.0f, 0.0f, 100.0f);
        SpawnedObject = GetWorld()->SpawnActor<AActor>(ObjectClassToSpawn, Location, FRotator::ZeroRotator);
        LastSpawnArea = SpawnArea;
        GetWorld()->GetTimerManager().SetTimer(LifeSpanTimer, this, &ARFSSpawnManager::ServerDestroySpawnedObject, LifeSpan, false);

        if (SpawnedObject)
        {
           if (IRFSDespawnableInterface* DespawnableActor = Cast<IRFSDespawnableInterface>(SpawnedObject))
           {
               DespawnableActor->OnDespawn().AddDynamic(this, &ARFSSpawnManager::ServerDestroySpawnedObject);
           }
        }
    }
}

void ARFSSpawnManager::ServerDestroySpawnedObject_Implementation()
{
    if (SpawnedObject)
    {
        SpawnedObject->Destroy();
        SpawnedObject = nullptr;
        ServerSpawnObject();
    }
}

AActor* ARFSSpawnManager::GetRandomSpawnArea()
{
    if (GetLocalRole() != ROLE_Authority)
    {
        return nullptr;
    }

    if (SpawnAreas.Num() <= 1)
    {
        return SpawnAreas.IsEmpty() ? nullptr : SpawnAreas[0];
    }

    TArray<AActor*> FilteredAreas = SpawnAreas.FilterByPredicate([this](AActor* Area)
        {
            return Area != LastSpawnArea;
        });

    if (FilteredAreas.Num() > 0)
    {
        int32 Index = FMath::RandRange(0, FilteredAreas.Num() - 1);
        return FilteredAreas[Index];
    }

    return nullptr;
}
