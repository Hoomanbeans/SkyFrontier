// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class SKYFRONTIER_API TCPClient : public FRunnable
{
public:
 TCPClient(class AMyPlayerState* pState);
 ~TCPClient();
 virtual bool Init();
 virtual uint32 Run();
 virtual void Stop();
 void CreateNewGameSession(FString sname);
 void JoinGameSession(int sID);
 bool IsConnected();
 
private:
 FRunnableThread* Thread;
 FSocket* Socket;
 FSocket* ListenerSocket;
 bool running;
 bool connected;
 class AMyPlayerState* PlayerState;
};
