// Fill out your copyright notice in the Description page of Project Settings.

#include "ToonTanksPlayerController.h"

void AToonTanksPlayerController::SetPlayerEnabledState(bool bPlayerEnabled)
{
    APawn *PlayerPawn = GetPawn();
    if (bPlayerEnabled)
    {
        PlayerPawn->EnableInput(this);
    }
    else
    {
        PlayerPawn->DisableInput(this);
    }
    bShowMouseCursor = bPlayerEnabled;
    PlayerPawn->SetActorTickEnabled(bPlayerEnabled);
}