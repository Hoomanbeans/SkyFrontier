#pragma once

#include "CoreMinimal.h"
#include "Net/UnrealNetwork.h"
#include "Components/ActorComponent.h"
#include "PointsComponent.generated.h"

DECLARE_EVENT_OneParam(UCPP_PointsComponent, PointsReceiveEvent, int)

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SKYFRONTIER_API UPointsComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPointsComponent();

	UFUNCTION(BlueprintCallable, Category = "Points")
	int GetP1Points() const;
	UFUNCTION(BlueprintCallable, Category = "Points")
int GetP2Points() const;
	
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Points")
		void AddP1Points(int PointsToAdd);
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Points")
	void AddP2Points(int PointsToAdd);

protected: // Functions

	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


public: // Events

	PointsReceiveEvent OnPointsReceiveEvent;

public:

	UPROPERTY(Replicated, VisibleAnywhere, Category = "Points")
	int P1Points;
	UPROPERTY(Replicated, VisibleAnywhere, Category = "Points")
	int P2Points;
};