// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "RaceForSurvivalCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharacterDiedDelegate, ARaceForSurvivalCharacter*, Character);

UCLASS(config=Game)
class ARaceForSurvivalCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

public:
	ARaceForSurvivalCharacter();
	
	virtual void PossessedBy(AController* NewController) override;

	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void Die();

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

	virtual void Tick(float DeltaSeconds) override;

	// I opted for TWeakObjectPtrs because I didn't want a shared hard reference here and I didn't want an extra function call of getting
	// the ASC/AttributeSet from the PlayerState or child classes every time I referenced them in this base class.
	TWeakObjectPtr<class URFSAbilitySystemComponent> AbilitySystemComponent;
	TWeakObjectPtr<class URFSAttributeSetBase> AttributeSetBase;

	virtual void SetHealth(float Health);

	UFUNCTION(BlueprintCallable, Category = "RFS|Character|Attributes")
	float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = "RFS|Character|Attributes")
	float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable, Category = "RFS|Character|Attributes")
	float GetPoints() const;

	UFUNCTION(BlueprintCallable, Category = "RFS|Character|Attributes")
	float GetHealthDamageRate() const;

	UFUNCTION(BlueprintCallable, Category = "RFS|Character|Attributes")
	float GetPointsIncreaseRate() const;

	UFUNCTION(BlueprintCallable, Category = "RFS|Character|Attributes")
	float GetTimeElapsed() const;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "RFS|GameplayEffects")
	TSubclassOf<class UGameplayEffect> DefaultAttributes;

	// These effects are only applied one time on startup
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "RFS|GameplayEffects")
	TArray<TSubclassOf<UGameplayEffect>> StartupEffects;

	virtual void InitializeAttributes();

	virtual void AddStartupEffects();

	FGameplayTag DeadTag;
	FGameplayTag EffectRemoveOnDeathTag;

	virtual void OnRep_PlayerState() override;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UPROPERTY(BlueprintAssignable, Category = "RFS|Character")
	FCharacterDiedDelegate OnCharacterDied;

	UFUNCTION(BlueprintCallable, Category = "RFS|Character")
	virtual bool IsAlive() const;
};

