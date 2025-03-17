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

public:
    ATower();

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

private:
    class ATank *Tank;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
    float FireRange = 1000.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
    float FireRate = 2.f; // Fire every 2 seconds

    double LastFireTime = 0.f;

    void CheckShootCondition();
    void Fire();

    bool TargetInRange();
    bool TargetVisible();
};
