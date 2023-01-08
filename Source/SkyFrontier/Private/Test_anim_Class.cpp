// Fill out your copyright notice in the Description page of Project Settings.


#include "Test_anim_Class.h"

// Sets default values
ATest_anim_Class::ATest_anim_Class()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATest_anim_Class::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATest_anim_Class::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATest_anim_Class::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

