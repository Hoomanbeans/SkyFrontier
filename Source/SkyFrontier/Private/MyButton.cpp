// Fill out your copyright notice in the Description page of Project Settings.


#include "MyButton.h"

UMyButton::UMyButton()
{
	OnClicked.AddDynamic(this, &UMyButton::OnClick);
}
void UMyButton::SetSessionInfo(int sID, TCPClient *tclient)
{
	sessionID = sID;  tcpClient = tclient;
}
void UMyButton::OnClick()
{
	tcpClient->JoinGameSession(sessionID);
}