// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Test_anim_Class.generated.h"

UCLASS()
class SKYFRONTIER_API ATest_anim_Class : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATest_anim_Class();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
