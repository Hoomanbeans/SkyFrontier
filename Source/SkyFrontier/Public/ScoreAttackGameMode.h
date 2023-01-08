#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PointsComponent.h"
#include "ScoreAttackGameMode.generated.h"

UCLASS()
class SKYFRONTIER_API AScoreAttackGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AScoreAttackGameMode();

	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(const float DeltaSeconds) override;

private:
	int GoalScore;
	bool bGameEnded;
	APawn* Pawn1;
	APawn* Pawn2;
	UPointsComponent* PointsComponent1;
	UPointsComponent* PointsComponent2;
	
};