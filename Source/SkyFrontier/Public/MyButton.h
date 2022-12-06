// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TCPClient.h"
#include "Components/Button.h"
#include "MyButton.generated.h"

/**
 * 
 */
UCLASS()
class SKYFRONTIER_API UMyButton : public UButton
{
	GENERATED_BODY()
public:
	UMyButton();
	void SetSessionInfo(int sID, TCPClient *tclient);
protected:  int sessionID;
	TCPClient *tcpClient;
	
	UFUNCTION()
	void OnClick();
	
};
