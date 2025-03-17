// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 *
 */
UCLASS()
class TOONTANK_API ATower : public ABasePawn
{
    GENERATED_BODY()
private:
    class ATank *Tank;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
    float FireRange = 1000.f;

    bool bCanFire = true;

public:
    ATower();
    bool TargetInRange();
    bool TargetVisible();

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
};
