#include "ScoreAttackGameMode.h"
#include "PointsComponent.h"
#include <Kismet/GameplayStatics.h>
#include "GameFramework/Controller.h"


AScoreAttackGameMode::AScoreAttackGameMode()
{
	GoalScore = 10;
}

void AScoreAttackGameMode::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawn::StaticClass(), FoundActors);
	
	if (FoundActors.Num() == 2)
	{
		Pawn1 = Cast<APawn>(FoundActors[0]);
		Pawn2 = Cast<APawn>(FoundActors[1]);

		if (Pawn1 && Pawn2)
		{
			PointsComponent1 = Pawn1->FindComponentByClass<UPointsComponent>();
			PointsComponent2 = Pawn2->FindComponentByClass<UPointsComponent>();
		}
	}
}

void AScoreAttackGameMode::BeginPlay()
{
	Super::BeginPlay();
	bGameEnded = false;
	UE_LOG(LogTemp, Warning, TEXT("IS THIS WORKING"));
}

void AScoreAttackGameMode::Tick(const float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (PointsComponent1 && PointsComponent2 && !bGameEnded)
	{
		if (PointsComponent1->Points >= GoalScore)
		{
			UE_LOG(LogTemp, Warning, TEXT("Player 1 Wins!"));
			bGameEnded = true;
		}
		else if (PointsComponent2->Points >= GoalScore)
		{
			UE_LOG(LogTemp, Warning, TEXT("Player 2 Wins!"));
			bGameEnded = true;
		}
	}
}