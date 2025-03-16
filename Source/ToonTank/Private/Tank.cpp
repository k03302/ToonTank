// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/PlayerController.h"

ATank::ATank()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ATank::BeginPlay()
{
    Super::BeginPlay();

    // Add the input mapping context to the player controller
    if (APlayerController *PlayerController = Cast<APlayerController>(GetController()))
    {
        if (UEnhancedInputLocalPlayerSubsystem *Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(InputMappingContext, 0);
        }
    }
}

void ATank::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Ensure the input component is an EnhancedInputComponent
    if (UEnhancedInputComponent *EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATank::Move);
        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATank::Look);
        EnhancedInputComponent->BindAction(RotateAction, ETriggerEvent::Triggered, this, &ATank::Rotate);
    }
}

void ATank::Move(const FInputActionValue &Value)
{
    float AxisValue = Value.Get<float>();
    UE_LOG(LogTemp, Warning, TEXT("Move: %f"), AxisValue);

    float DeltaTime = GetWorld()->GetDeltaSeconds();
    FVector Movement = GetActorForwardVector() * AxisValue * MovementSpeed * DeltaTime;
    AddActorWorldOffset(Movement, true);
}

void ATank::Look(const FInputActionValue &Value)
{
    // Get the input vector (X = Yaw, Y = Pitch)
    FVector2D LookVector = Value.Get<FVector2D>();
    UE_LOG(LogTemp, Warning, TEXT("Look: %s"), *LookVector.ToString());
}

void ATank::Rotate(const FInputActionValue &Value)
{
    float AxisValue = Value.Get<float>();
    UE_LOG(LogTemp, Warning, TEXT("Rotate: %f"), AxisValue);

    float DeltaTime = GetWorld()->GetDeltaSeconds();
    FRotator Rotation = FRotator(0.f, DeltaTime * RotateSpeed * AxisValue, 0.f);
    AddActorWorldRotation(Rotation, true);
}