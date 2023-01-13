#include "HealthSystem.h"
#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"
#include "Components/ActorComponent.h"

UHealthSystem::UHealthSystem()
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
	SetIsReplicated(true);
	MaxHealth = 100;
}

void UHealthSystem::BeginPlay()
{
	Super::BeginPlay();
	Health = MaxHealth;
	Shield = 0;
}

void UHealthSystem::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UHealthSystem, Health);
}

float UHealthSystem::GetHealth() const
{
	return Health;
}

float UHealthSystem::GetMaxHealth() const
{
	return MaxHealth;
}

float UHealthSystem::GetShield() const
{
	return Shield;
}

void UHealthSystem::TakeDamage(const float Amount)
{
	if (Amount > 0)
	{
		Health -= Amount;

		OnDamageTakenEvent.Broadcast(Amount);
	}
}



void UHealthSystem::RecoverHealth(const float Amount)
{
	if (Amount > 0)
	{
		Health += Amount;
		if (Health >= MaxHealth)
		{
			Health = MaxHealth;
		}

		OnDamageHealedEvent.Broadcast(Amount);
	}
}

void UHealthSystem::ReceiveShield(const float Amount)
{
	if (Amount >= 0)
	{
		Shield += Amount;

		OnShieldReceiveEvent.Broadcast(Amount);
	}
}

void UHealthSystem::RemoveShield(const float Amount)
{
	if (Amount >= 0)
	{
		Shield -= Amount;

		if (Shield < 0)
		{
			Shield = 0;
		}
		OnShieldReceiveEvent.Broadcast(Amount);
	}
}