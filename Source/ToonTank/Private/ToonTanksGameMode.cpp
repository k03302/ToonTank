// Fill out your copyright notice in the Description page of Project Settings.

#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"

bool AToonTanksGameMode::ActorDied(AActor *DeadActor)
{
    if (ATank *Tank = Cast<ATank>(DeadActor))
    {
        Tank->HandleDestruction();
        if (AToonTanksPlayerController *PlayerController = Cast<AToonTanksPlayerController>(Tank->GetController()))
        {
            PlayerController->SetPlayerEnabledState(false);
        }
        GameOver(false);
        return true;
    }
    else if (ATower *Tower = Cast<ATower>(DeadActor))
    {
        Tower->HandleDestruction();
        --TargetTowers;
        if (TargetTowers == 0)
        {
            GameOver(true);
        }

        UE_LOG(LogTemp, Warning, TEXT("Tower Destroyed! Remaining Towers: %i"), TargetTowers);
        return true;
    }

    return false;
}

void AToonTanksGameMode::BeginPlay()
{
    Super::BeginPlay();

    TargetTowers = GetTaregetTowerCount();

    PlayerTank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    if (AToonTanksPlayerController *PlayerController = Cast<AToonTanksPlayerController>(PlayerTank->GetController()))
    {
        PlayerController->SetPlayerEnabledState(false);

        FTimerHandle StartTimerHandle;
        FTimerDelegate StartGameDelegate = FTimerDelegate::CreateUObject(
            PlayerController,
            &AToonTanksPlayerController::SetPlayerEnabledState,
            true);
        GetWorldTimerManager().SetTimer(StartTimerHandle, StartGameDelegate, StartDelay, false);
    }

    StartGame();
}

int32 AToonTanksGameMode::GetTaregetTowerCount()
{
    TArray<AActor *> Towers;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATower::StaticClass(), Towers);
    return Towers.Num();
}