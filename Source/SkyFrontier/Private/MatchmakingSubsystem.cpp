// Fill out your copyright notice in the Description page of Project Settings.


#include "MatchmakingSubsystem.h"


void UMatchmakingSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	// Force the intiialization of any other dependency you might have
	//Collection.InitializeDependency();
	Super::Initialize(Collection);
}

void UMatchmakingSubsystem::RequestGame(FString LevelName)
{
	FindMatchJob = new MatchmakingJob(CurrentState, LevelName);
	FindMatchJob->JobCompletedEvent.AddUFunction(this, "OnMatchmakerThreadDone");
		
	FRunnableThread::Create(FindMatchJob, TEXT("FindMatchJob"));
}

void UMatchmakingSubsystem::OnMatchmakerThreadDone(bool CompletionState, FString ServerIP, FString LevelName)
{
	if(CompletionState)
		MatchFoundEvent.Broadcast(ServerIP, LevelName);
	else ServerToConnectTo = "Failed To Connect!";
}
