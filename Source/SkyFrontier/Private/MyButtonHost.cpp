// Fill out your copyright notice in the Description page of Project Settings.


#include "MyButtonHost.h"

UMyButtonHost::UMyButtonHost()
{
	OnClicked.AddDynamic(this, &UMyButtonHost::OnClick);
}
void UMyButtonHost::SetSessionInfo(FString sname, TCPClient *tclient)
{
	sessionName = sname;  tcpClient = tclient;
}
void UMyButtonHost::OnClick()
{
	tcpClient->CreateNewGameSession(sessionName);
}	