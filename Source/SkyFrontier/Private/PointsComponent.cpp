#include "PointsComponent.h"
#include "Net/UnrealNetwork.h"

UPointsComponent::UPointsComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

void UPointsComponent::BeginPlay()
{
	Super::BeginPlay();
	P1Points = 0;
	P2Points = 0;
}

void UPointsComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UPointsComponent, P1Points);
	DOREPLIFETIME(UPointsComponent, P2Points);
}

int UPointsComponent::GetP1Points() const
{
	return P1Points;
}

int UPointsComponent::GetP2Points() const
{
	return P2Points;
}

void UPointsComponent::AddP1Points_Implementation(const int PointsToAdd)
{
	P1Points += PointsToAdd;

	OnPointsReceiveEvent.Broadcast(PointsToAdd);
}

void UPointsComponent::AddP2Points_Implementation(const int PointsToAdd)
{
	P2Points += PointsToAdd;

	OnPointsReceiveEvent.Broadcast(PointsToAdd);
}