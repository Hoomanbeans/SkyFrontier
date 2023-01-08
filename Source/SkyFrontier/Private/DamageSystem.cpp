#include "DamageSystem.h"

// Sets default values for this component's properties
UDamageSystem::UDamageSystem()
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}


// Called when the game starts
void UDamageSystem::BeginPlay()
{
	Super::BeginPlay();	
}

float UDamageSystem::GetShootingDamage() const
{
	return ShootingDamage;
}

float UDamageSystem::GetMissileDamage() const
{
	return MissileDamage;
}

void UDamageSystem::MultiplyDamage(const float Amount)
{
	if(Amount >= 0)
	{
		ShootingDamage *= Amount;
		MissileDamage *= Amount;
	
		OnIncreaseDamageEvent.Broadcast(Amount);
	}
}

void UDamageSystem::RestoreDamage(const float Amount)
{
	if(Amount >= 0)
	{
		ShootingDamage /= Amount;
		MissileDamage /= Amount;
	
		OnIncreaseDamageEvent.Broadcast(Amount);
	}
}

