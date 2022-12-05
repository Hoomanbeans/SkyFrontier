// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerState.h"

#include "MyButton.h"
#include "TCPClient.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"

void AMyPlayerState::BeginPlay()
{
	FString levelName = GetWorld()->GetMapName();
	levelName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);
	if (levelName == "StartMap")
	{
		tcpClient = new TCPClient(this);
		canConnectToGameServer = false;
		if ((MatchmakingWidgetClass) && (tcpClient->IsConnected()))
		{
			serversList = new TArray<FSessionInfo*>();
			GetWorld()->GetTimerManager().SetTimer(serverListTimerHandle,  this, &AMyPlayerState::OnUpdateServerList, 2, true);
			MatchmakingWidget = CreateWidget<UUserWidget>(GetWorld(),MatchmakingWidgetClass);
			MatchmakingWidget->AddToViewport();
			serverListScrollBoxWidget = Cast<UScrollBox>(MatchmakingWidget->GetWidgetFromName(TEXT("MyScrollBox")));
			UButton* newSessionButton = Cast<UButton>(MatchmakingWidget->GetWidgetFromName(TEXT("NewSession")));
			if (newSessionButton)
			{	
				newSessionButton->SetIsEnabled(true);
				newSessionButton->OnClicked.AddDynamic(this,  &AMyPlayerState::OnNewSessionClicked);
			}
		}
	}
}
void AMyPlayerState::OnNewSessionClicked()
{
	tcpClient->CreateNewGameSession("My test session");
}
void AMyPlayerState::UpdateSessionsList(FString serverinfo)
{
	TArray<FString> Out;  serverinfo.ParseIntoArray(Out, TEXT("|"), true);
	for (int i = 1; i < Out.Num() - 1; i += 2) {  FSessionInfo *tempInfo = new FSessionInfo();
		tempInfo->id = FCString::Atoi(*Out[i]);
		tempInfo->name = Out[i + 1];
		tempInfo->serverip = "";
		tempInfo->serverport = -1;
		serversList->Add(tempInfo);  }
}
void AMyPlayerState::ConnectToGameServer(FSessionInfo session)
{
	canConnectToGameServer = true;  connectToGameServerSession = session;
}
void AMyPlayerState::OnUpdateServerList()  {
	if (tcpClient) {
		if (tcpClient->IsConnected()) {
			if (serversList->Num() > 0) {
				if ((MatchmakingWidget) && (serverListScrollBoxWidget)) {
					TArray<UWidget*> allChildren = serverListScrollBoxWidget->  GetAllChildren();
					for (int i = 0; i < allChildren.Num(); i++)
					{
						allChildren[i]->RemoveFromParent();
					}
					for (int i = 0; i < serversList->Num(); i++)
					{
						UVerticalBox* ItemWidgetsBox = NewObject<UVerticalBox>();
						serverListScrollBoxWidget->AddChild(ItemWidgetsBox);
						UMyButton* ItemWidget = NewObject<UMyButton>(this);
						ItemWidget->SetSessionInfo((*serversList)[i]->id,  tcpClient);
						UTextBlock* ItemWidgetText = NewObject<UTextBlock>();
						ItemWidgetText->SetText(FText::FromString(  (*serversList)[i]->name));
						ItemWidget->AddChild(ItemWidgetText);
						UVerticalBoxSlot* Slot = ItemWidgetsBox->  AddChildToVerticalBox(ItemWidget);
						static FMargin Padding(5);
						Slot->SetPadding(Padding);
					}
				}
			}
			if (canConnectToGameServer){  APlayerController* pController = GetWorld()->  GetFirstPlayerController();
				if (pController){  FString cmd = "open " + connectToGameServerSession.serverip + ":" + FString::FromInt(connectToGameServerSession.serverport);
					tcpClient->Stop();
					canConnectToGameServer = false;
					MatchmakingWidget->RemoveFromViewport();
					pController->ConsoleCommand(cmd);
				}
			}
		}
	}
}