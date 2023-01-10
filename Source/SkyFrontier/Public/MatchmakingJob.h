// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// Bool if it did it's job correctly and the ip:port to connect to.
DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnMatchMakerThreadCompleted, bool, FString, FString);

// Declaration Of All The Messages The Clients Are Allowed To Send AKA The Message ID's
#define CLIENT_MESSAGE_REQUESTCONNECTION 1
#define CLIENT_MESSAGE_CONFIRMDONE 2

class SKYFRONTIER_API MatchmakingJob : public FRunnable
{
public:
	// Dissalow default construction of this objects
	// Simple example, but you could control the copy/move contructors and copy/move operators too!
	MatchmakingJob();
	explicit MatchmakingJob(FString& stateToWriteInto, FString LevelName);

private:
	// Do your setup here, allocate memory, ect.
	virtual bool Init() override;

	// Main data processing happens here
	virtual uint32 Run() override;

	// Called when thread is done
	virtual void Exit() override;
	
	// Clean up any memory you allocated here happens when a stop is requested
	virtual void Stop() override;

	void SleepThread();
	
	// Reference To Strings That Exist In The Matchmaking System, Thread Writes Directly Into Them!
	FString& currentState;

	// Level To Load
	FString LevelToLoad;
	
	// Pointer To Our Current Socket Object
	FSocket* ConnectionSocket;

public:
	FOnMatchMakerThreadCompleted JobCompletedEvent;
};