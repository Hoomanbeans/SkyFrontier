// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TCPClient.h"
#include "Components/Button.h"
#include "MyButtonHost.generated.h"

/**
 * 
 */
UCLASS()
class SKYFRONTIER_API UMyButtonHost : public UButton
{
	GENERATED_BODY()
public:
	UMyButtonHost();
	void SetSessionInfo(FString sname, TCPClient *tclient);
protected:  FString sessionName;
	TCPClient *tcpClient;
	
	UFUNCTION()
	void OnClick();
	
};