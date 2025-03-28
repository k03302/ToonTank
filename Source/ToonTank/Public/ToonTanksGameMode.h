// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

/**
 *
 */
UCLASS()
class TOONTANK_API AToonTanksGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    bool ActorDied(AActor *DeadActor);

private:
    class ATank *PlayerTank;

protected:
    virtual void BeginPlay() override;
};
