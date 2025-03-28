// Fill out your copyright notice in the Description page of Project Settings.

#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "GameFramework/PlayerController.h"

bool AToonTanksGameMode::ActorDied(AActor *DeadActor)
{
    if (ATank *Tank = Cast<ATank>(DeadActor))
    {
        Tank->HandleDestruction();
        if (APlayerController *PlayerController = Cast<APlayerController>(Tank->GetController()))
        {
            Tank->DisableInput(PlayerController);
        }
        return true;
    }
    else if (ATower *Tower = Cast<ATower>(DeadActor))
    {
        Tower->HandleDestruction();
        return true;
    }

    return false;
}

void AToonTanksGameMode::BeginPlay()
{
    Super::BeginPlay();

    PlayerTank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}