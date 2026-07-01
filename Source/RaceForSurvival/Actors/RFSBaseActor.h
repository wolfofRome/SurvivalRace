// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RFSBaseActor.generated.h"

UCLASS()
class RACEFORSURVIVAL_API ARFSBaseActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ARFSBaseActor();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnBeginOverlap(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere)
	class UNiagaraComponent* NiagaraEffectComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RFS|Sound")
	class USoundCue* Sound;

	void ClientPlaySound();
	void ClientPlaySound_Implementation();
};
