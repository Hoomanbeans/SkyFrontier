// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MatchmakingJob.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MatchmakingSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMatchFound, FString, ServerIP);

UCLASS()
class SKYFRONTIER_API UMatchmakingSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	// Start Requesting A Game Launch the thread and the widget can poll the string value for an update till the threads done.
	UFUNCTION(BlueprintCallable)
	void RequestGame();

	// Callback From The Thread When It's Done
	UFUNCTION()
	void OnMatchmakerThreadDone(bool CompletionState, FString ServerIP);
	
	// String the blueprint widget will look at
	UPROPERTY(BlueprintReadOnly)
	FString CurrentState;

	UPROPERTY(BlueprintReadOnly)
	FString ServerToConnectTo;
	
	// Actual Threaded Job
	MatchmakingJob* FindMatchJob;

	// Event To Let Someone Else Handle The Level Loading Stuff
	UPROPERTY(BlueprintAssignable)
	FOnMatchFound MatchFoundEvent;
};

