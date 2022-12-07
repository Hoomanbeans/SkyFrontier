// Fill out your copyright notice in the Description page of Project Settings.


#include "TCPClient.h"

#include "MyPlayerState.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "TraceServices/Model/Diagnostics.h"

TCPClient::TCPClient(AMyPlayerState* pState)
{
	Thread = FRunnableThread::Create(this, TEXT("TCPClientThread"), 0,  TPri_Normal);  PlayerState = pState;
}
TCPClient::~TCPClient()
{
	TCPClient::Stop();  delete Thread;
}
void TCPClient::Stop()
{
	running = false;
}
bool TCPClient::IsConnected()
{
	return connected;
}

bool TCPClient::Init()
{
	Socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("default"), false);
	int32 NewSize = 0;
	Socket->SetReceiveBufferSize(1024, NewSize);
	FIPv4Address matchmakingServerIP(127, 0, 0, 1);
	TSharedRef<FInternetAddr> matchmakingServer = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	matchmakingServer->SetIp(matchmakingServerIP.Value);
	matchmakingServer->SetPort(8856);
	
	connected = Socket->Connect(*matchmakingServer);
	if (connected)
	{
		UE_LOG(LogTemp, Log, TEXT("CONNECTED!"));
		FString serialized = TEXT("g|#");
		TCHAR *serializedChar = serialized.GetCharArray().GetData();
		int32 size = FCString::Strlen(serializedChar);
		int32 sent = 0;
		bool successful = Socket->Send((uint8*)TCHAR_TO_UTF8(serializedChar), size, sent);
		if (successful)
			{UE_LOG(LogTemp, Log, TEXT("MESSAGE SENT!"));
			return true;
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("ERROR: NOT CONNECTED!"));return false;
		}
	}
	return 0;
}
	uint32 TCPClient::Run()
	{
		running = true;
		TArray<uint8> ReceivedData;
		while (running)
		{
			uint32 Size = 0;
			if (Socket->HasPendingData(Size))
			{
				ReceivedData.Init(0, Size);
				int32 Read = 0;
				Socket->Recv(ReceivedData.GetData(), ReceivedData.Num(), Read);
				FString ServerMessage = FString(UTF8_TO_TCHAR(ReceivedData.GetData()));
				UE_LOG(LogTemp, Log, TEXT("RECEIVED: %s"), *ServerMessage);
				if ((ServerMessage[0] == 's') && (PlayerState))
				{
					PlayerState->UpdateSessionsList(ServerMessage);
				}
				else if((ServerMessage[0] == 'o') && (PlayerState))
				{
					TArray<FString> Out;
					ServerMessage.ParseIntoArray(Out, TEXT("|"), true);
					FSessionInfo session;
					session.id = -1;
					session.name = "";
					session.serverip = Out[1];
					session.serverport = FCString::Atoi(*Out[2]);
					PlayerState->ConnectToGameServer(session);
				}
			}
		}
		return 0;
	}
	
	void TCPClient::CreateNewGameSession(FString sname)
	{
		FString serialized = "c|" + sname + "|#";
		TCHAR *serializedChar = serialized.GetCharArray().GetData();
		int32 size = FCString::Strlen(serializedChar);
		int32 sent = 0;
		bool successful = Socket->Send((uint8*)  TCHAR_TO_UTF8(serializedChar), size, sent);
		if (successful)  UE_LOG(LogTemp, Log, TEXT("MESSAGE SENT!!!!"));
	}
	void TCPClient::JoinGameSession(int sID)
	{
		FString serialized = "j|" + FString::FromInt(sID) + "|#";
		TCHAR *serializedChar = serialized.GetCharArray().GetData();
		int32 size = FCString::Strlen(serializedChar);
		int32 sent = 0;
		bool successful = Socket->Send((uint8*)  TCHAR_TO_UTF8(serializedChar), size, sent);
		if (successful)  UE_LOG(LogTemp, Log, TEXT("MESSAGE SENT!!!!"));
	}