// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "InputActionValue.h" // Required for Enhanced Input
#include "Tank.generated.h"

/**
 *
 */
UCLASS()
class TOONTANK_API ATank : public ABasePawn
{
    GENERATED_BODY()

public:
    ATank();

protected:
    virtual void BeginPlay() override;

public:
    virtual void SetupPlayerInputComponent(UInputComponent *PlayerInputComponent) override;

private:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (AllowPrivateAccess = "true"))
    class UInputMappingContext *InputMappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (AllowPrivateAccess = "true"))
    class UInputAction *MoveAction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (AllowPrivateAccess = "true"))
    class UInputAction *RotateAction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (AllowPrivateAccess = "true"))
    class UInputAction *LookAction;

    // Movement and Look functions
    void Move(const FInputActionValue &Value);
    void Rotate(const FInputActionValue &Value);
    void Look(const FInputActionValue &Value);
};
