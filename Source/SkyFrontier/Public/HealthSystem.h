#pragma once

#include "CoreMinimal.h"
#include "Net/UnrealNetwork.h"
#include "Components/ActorComponent.h"
#include "HealthSystem.generated.h"

DECLARE_EVENT_OneParam(UCPP_HealthComponent, DamageTakenEvent, float)
DECLARE_EVENT_OneParam(UCPP_HealthComponent, HealDamageEvent, float)
DECLARE_EVENT_OneParam(UCPP_HealthComponent, ShieldReceiveEvent, float)

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
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
		float GetShield() const;

	UFUNCTION(BlueprintCallable)
		void TakeDamage(float Amount);
	UFUNCTION(BlueprintCallable)
		void RecoverHealth(float Amount);
	UFUNCTION(BlueprintCallable)
		void ReceiveShield(float Amount);
	UFUNCTION(BlueprintCallable)
		void RemoveShield(float Amount);

protected: // Functions

	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public: // Events

	DamageTakenEvent OnDamageTakenEvent;
	HealDamageEvent OnDamageHealedEvent;
	ShieldReceiveEvent OnShieldReceiveEvent;

private: // This can be protected if we want to subclass the Health Component

	UPROPERTY(Replicated, VisibleAnywhere)
		float Health;
	UPROPERTY(EditAnywhere)
		float MaxHealth;
	UPROPERTY(VisibleAnywhere)
		float Shield;
};
