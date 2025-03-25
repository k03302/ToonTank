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

void ATank::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    LookAtMouse();
}

void ATank::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Ensure the input component is an EnhancedInputComponent
    if (UEnhancedInputComponent *EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATank::Move);
        EnhancedInputComponent->BindAction(RotateAction, ETriggerEvent::Triggered, this, &ATank::Rotate);
        EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Started, this, &Super::Shoot);
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

void ATank::Rotate(const FInputActionValue &Value)
{
    float AxisValue = Value.Get<float>();
    UE_LOG(LogTemp, Warning, TEXT("Rotate: %f"), AxisValue);

    float DeltaTime = GetWorld()->GetDeltaSeconds();
    FRotator Rotation = FRotator(0.f, DeltaTime * RotateSpeed * AxisValue, 0.f);
    AddActorWorldRotation(Rotation, true);
}

void ATank::LookAtMouse()
{
    if (APlayerController *PlayerController = Cast<APlayerController>(GetController()))
    {
        FHitResult MouseHitResult;
        PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, MouseHitResult);
        LookAt(MouseHitResult.bBlockingHit ? MouseHitResult.ImpactPoint : MouseHitResult.TraceEnd);
        DrawDebugSphere(GetWorld(), MouseHitResult.ImpactPoint, 5.f, 12, FColor::Red, false, 3.f);

        // UE_LOG(LogTemp, Warning, TEXT("MouseHitResult: %d %f %s %s"), MouseHitResult.bBlockingHit, MouseHitResult.Distance, *MouseHitResult.TraceEnd.ToString(),
        //        *MouseHitResult.ImpactPoint.ToString());
    }
}

void ATank::HandleDestruction()
{
    Super::HandleDestruction();
}