// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthSystem.h"

UHealthSystem::UHealthSystem()
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

void UHealthSystem::BeginPlay()
{
	Super::BeginPlay();
	
	Health = MaxHealth;
	Shield = 0;
}

float UHealthSystem::GetHealth() const
{
	return Health;
}

float UHealthSystem::GetMaxHealth() const
{
	return MaxHealth;
}

float UHealthSystem::GetHealthAsPercentage() const
{
	return Health / MaxHealth;
}

float UHealthSystem::GetShield() const
{
	return Shield;
}

void UHealthSystem::ModifyHealth(const float Amount)
{
	if(Amount == 0)
		return;
	
	Health += Amount;

	Amount > 0 ? OnDamageHealedEvent.Broadcast(Amount) : OnDamageTakenEvent.Broadcast(Amount);
}

void UHealthSystem::TakeDamage(const float Amount)
{
	if(Amount > 0)
	{
		Health -= Amount;

		OnDamageTakenEvent.Broadcast(Amount);
	}
}
 
void UHealthSystem::RecoverHealth(const float Amount)
{
	if(Amount > 0)
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
	if(Amount >= 0)
	{
		Shield += Amount;
	
		OnShieldReceiveEvent.Broadcast(Amount);
	}
}

void UHealthSystem::RemoveShield(const float Amount)
{
	if(Amount >= 0)
	{
		Shield -= Amount;
		
		if (Shield < 0)
		{
			Shield = 0;
		}
		OnShieldReceiveEvent.Broadcast(Amount);
	}
}