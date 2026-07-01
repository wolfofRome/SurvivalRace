// Fill out your copyright notice in the Description page of Project Settings.


#include "RFSBaseActor.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

ARFSBaseActor::ARFSBaseActor()
{
	PrimaryActorTick.bCanEverTick = true;

    bReplicates = true;
    bAlwaysRelevant = true;

    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    RootComponent->Mobility = EComponentMobility::Static;

    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    MeshComponent->SetupAttachment(RootComponent);

    CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
    CollisionComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
    CollisionComponent->SetupAttachment(MeshComponent);
    CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ARFSBaseActor::OnBeginOverlap);

    NiagaraEffectComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraEffectComponent"));
	NiagaraEffectComponent->SetupAttachment(MeshComponent);
}

void ARFSBaseActor::BeginPlay()
{
	Super::BeginPlay();
}

void ARFSBaseActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		ClientPlaySound();
	}
}

void ARFSBaseActor::ClientPlaySound_Implementation()
{
	if (Sound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			this,
			Sound,
			GetActorLocation()
		);
	}
}

void ARFSBaseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

