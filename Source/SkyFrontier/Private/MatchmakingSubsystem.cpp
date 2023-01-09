// Fill out your copyright notice in the Description page of Project Settings.


#include "MatchmakingSubsystem.h"


void UMatchmakingSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	// Force the intiialization of any other dependency you might have
	//Collection.InitializeDependency();
	Super::Initialize(Collection);
}

void UMatchmakingSubsystem::RequestGame()
{
	FindMatchJob = new MatchmakingJob(CurrentState);
	FindMatchJob->JobCompletedEvent.AddUFunction(this, "OnMatchmakerThreadDone");
		
	FRunnableThread::Create(FindMatchJob, TEXT("FindMatchJob"));
}

void UMatchmakingSubsystem::OnMatchmakerThreadDone(bool CompletionState, FString ServerIP)
{
	if(CompletionState)
		MatchFoundEvent.Broadcast(ServerIP);
	else ServerToConnectTo = "Failed To Connect!";
}
