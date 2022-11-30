// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthSystem.generated.h"

DECLARE_EVENT_OneParam(UCPP_HealthComponent, DamageTakenEvent, float )
DECLARE_EVENT_OneParam(UCPP_HealthComponent, HealDamageEvent, float )

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SKYFRONTIER_API UHealthSystem : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthSystem();
	
	UFUNCTION(BlueprintPure)
	float GetHealth() const;
	UFUNCTION(BlueprintPure)
	float GetMaxHealth() const;
	UFUNCTION(BlueprintPure)
	float GetHealthAsPercentage() const;

	UFUNCTION(BlueprintCallable)
	void ModifyHealth(float Amount);

	UFUNCTION(BlueprintCallable)
	void TakeDamage(float Amount);
	UFUNCTION(BlueprintCallable)
	void RecoverHealth(float Amount);

protected: // Functions

	virtual void BeginPlay() override;	
	
public: // Events

	DamageTakenEvent OnDamageTakenEvent;
	HealDamageEvent OnDamageHealedEvent;

private: // This can be protected if we want to subclass the Health Component

	UPROPERTY(VisibleAnywhere)
	float Health;
	UPROPERTY(EditAnywhere)
	float MaxHealth;
		
};
