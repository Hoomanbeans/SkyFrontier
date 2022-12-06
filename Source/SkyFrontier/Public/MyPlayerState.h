// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MyPlayerState.generated.h"

USTRUCT()
struct FSessionInfo 
{  
  GENERATED_BODY()
  UPROPERTY()
  int id;
  UPROPERTY()
  FString name;
  UPROPERTY()
  FString serverip;
  UPROPERTY()
  int serverport;
};

UCLASS()
class SKYFRONTIER_API AMyPlayerState : public APlayerState
{
  GENERATED_BODY()
public:
  void UpdateSessionsList(FString serverinfo);
  void ConnectToGameServer(FSessionInfo session);
  
protected:
  virtual void BeginPlay() override;
  
  class TCPClient* tcpClient;
  
  UPROPERTY(EditDefaultsOnly, Category = "UI")
  TSubclassOf<class UUserWidget> MatchmakingWidgetClass;
  class UUserWidget* MatchmakingWidget;
  class UScrollBox* serverListScrollBoxWidget;
  
  TArray<FSessionInfo*> *serversList;
  FTimerHandle serverListTimerHandle;
  
  bool canConnectToGameServer;
  FSessionInfo connectToGameServerSession;
  
  UFUNCTION() 
  void OnNewSessionClicked();
  
  UFUNCTION()
  void OnUpdateServerList();
};
