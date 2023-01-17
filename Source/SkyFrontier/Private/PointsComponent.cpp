#include "PointsComponent.h"
#include "Net/UnrealNetwork.h"

UPointsComponent::UPointsComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
	SetIsReplicatedByDefault(true);
}

void UPointsComponent::BeginPlay()
{
	Super::BeginPlay();
	Points = 0;
}

void UPointsComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UPointsComponent, Points);
}

int UPointsComponent::GetPoints() const
{
	return Points;
}

void UPointsComponent::AddPoints_Implementation(const int PointsToAdd)
{
	Points += PointsToAdd;

	OnPointsReceiveEvent.Broadcast(PointsToAdd);
}