// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthSystem.h"

UHealthSystem::UHealthSystem()
{
	// This is a component that doesn't need a tick so lets disable it
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

void UHealthSystem::BeginPlay()
{
	Super::BeginPlay();

	// This is here for now, but if you ever do anything serialization related you might not want this.
	Health = MaxHealth;
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

		OnDamageHealedEvent.Broadcast(Amount);
	}
}