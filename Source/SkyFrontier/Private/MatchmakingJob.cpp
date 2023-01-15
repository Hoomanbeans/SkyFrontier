#include "MatchmakingJob.h"
#include "Sockets.h"
#include "Interfaces/IPv4/IPv4Endpoint.h"

#pragma optimize("", off)

MatchmakingJob::MatchmakingJob(FString& stateToWriteInto)
	: currentState(stateToWriteInto)
{}

bool MatchmakingJob::Init()
{
	const FIPv4Endpoint RemoteAddressForConnection = FIPv4Endpoint(FIPv4Address(127, 0, 0, 1), 1336);
	ConnectionSocket = ISocketSubsystem::Get()->CreateSocket("Stream", "MatchmakingServer");
	if(!ConnectionSocket)
	{
		return false;
	}

	const TSharedRef<FInternetAddr> Address = ISocketSubsystem::Get()->CreateInternetAddr(RemoteAddressForConnection.Address.Value, RemoteAddressForConnection.Port);
	return ConnectionSocket->Connect(Address.Get());
}

uint32 MatchmakingJob::Run()
{
	// Let's Start Connecting To The Matchmaking Server And Send Some Requests!
	currentState = "Connected To matchmaking Server!";
	// As the system is super fast we're adding these in here to showcase the system working, you'd never use them otherwise
	SleepThread();

#pragma region SendRequest
    // Let's Send A Request!
    // In this case we use a super simple way to send messages across, but we can add more to the string to parameterize certain things like gamemodes etc just make sure the server knows how to read the parameters
    // (you make those rules)
	// Creation of scope to reuse variable names for this example
    FString Serialized = FString::FromInt(CLIENT_MESSAGE_REQUESTCONNECTION);
	const TCHAR* serializedChar = Serialized.GetCharArray().GetData();
    int32 Size = FCString::Strlen(serializedChar);
    int32 Sent = 0;

    // This should be a while until you've sent all the bytes through, as this is super simple it'll always send the full message
    if(!ConnectionSocket->Send(reinterpret_cast<uint8*>(TCHAR_TO_UTF8(serializedChar)), Size, Sent))
    {
        // Some Error Message
    	JobCompletedEvent.Broadcast(false, "");
    	return 1; // Returns an exit code, you can use this to figure out where something failed or the type of failure
    }

	// Let The UI Know What's Going On
    currentState = "Request Sent! Waiting For Server To Find Match";
	SleepThread();
#pragma endregion 

#pragma region ReceiveReply
	// Now The Request Went To The Server, Let's Read And Wait For Their Reply!
	uint8 ReceiveBuffer[128];
    FMemory::Memset(ReceiveBuffer, 0, sizeof(uint8) * 128);
    int32 BytesRead = 0;

    FString FullMessage = "";

	// Again Our Examples Are Small But Bigger Data Would Be Read In Chunks And Reconstructed
    // Block and wait for a message to return, then read all remaining bits of said message
    if(!ConnectionSocket->Recv(ReceiveBuffer, 128, BytesRead))
    {
	    // Some Error Use something like FScoket::GetLastError (I dont remember the exact syntax) ESocketError Return Type
    	JobCompletedEvent.Broadcast(false, "");
    	return 2;
    }
	// Reinterpret the bits back into a const char* and apply it to the FString
    FullMessage.Append(reinterpret_cast<const char*>(ReceiveBuffer));
	
	currentState = "Ready To Connect To Server!: " + FullMessage;
	FPlatformProcess::Sleep(1.0f);
#pragma endregion 

#pragma region SendConfirmation
	// Tell The Server We're Done!
	// Reusing Variables, you could and SHOULD place these into smaller easier to read functions
    Serialized = TEXT( "" + FString::FromInt(CLIENT_MESSAGE_CONFIRMDONE) );
    serializedChar = Serialized.GetCharArray().GetData();
    Size = FCString::Strlen(serializedChar);
    Sent = 0;

    // This should be a while until you've sent all the bytes through, as this is super simple it'll always send the full message
    if(!ConnectionSocket->Send(reinterpret_cast<uint8*>(TCHAR_TO_UTF8(serializedChar)), Size, Sent))
    {
        // Some Error Message
    	JobCompletedEvent.Broadcast(false, "");
    	return 3;
    }
#pragma endregion
	
	JobCompletedEvent.Broadcast(true, FullMessage);

	return 0; // return the error! None in this case! :D
}

void MatchmakingJob::Exit()
{
	FRunnable::Exit();
}

void MatchmakingJob::Stop()
{
	FRunnable::Stop();
}

void MatchmakingJob::SleepThread()
{
#if !UE_BUILD_SHIPPING
	FPlatformProcess::Sleep(1.0f);
#endif
}

#pragma optimize("", on)