#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DamageSystem.generated.h"

DECLARE_EVENT_OneParam(UCPP_DamageComponent, IncreaseDamageEvent, float )
DECLARE_EVENT_OneParam(UCPP_DamageComponent, DecreaseDamageEvent, float )

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SKYFRONTIER_API UDamageSystem : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDamageSystem();

	UFUNCTION(BlueprintPure)
	float GetShootingDamage() const;
	UFUNCTION(BlueprintPure)
	float GetMissileDamage() const;

	UFUNCTION(BlueprintCallable)
	void MultiplyDamage(float Amount);
	UFUNCTION(BlueprintCallable)
	void RestoreDamage(float Amount);
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
public: // Events
	IncreaseDamageEvent OnIncreaseDamageEvent;
	DecreaseDamageEvent OnDecreaseDamageEvent;
	
private: // This can be protected if we want to subclass the Health Component

	UPROPERTY(EditAnywhere)
	float ShootingDamage;
	UPROPERTY(EditAnywhere)
	float MissileDamage;
		
};
