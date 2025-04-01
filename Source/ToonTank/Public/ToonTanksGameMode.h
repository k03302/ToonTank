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

    float StartDelay = 3.f;

    int32 TargetTowers = 0;

    int32 GetTaregetTowerCount();

protected:
    virtual void BeginPlay() override;

    UFUNCTION(BlueprintImplementableEvent)
    void StartGame();

    UFUNCTION(BlueprintImplementableEvent)
    void GameOver(bool bWonGame);
};
