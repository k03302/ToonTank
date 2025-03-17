// Fill out your copyright notice in the Description page of Project Settings.

#include "Tower.h"
#include "Tank.h"

ATower::ATower()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ATower::BeginPlay()
{
    Super::BeginPlay();

    Tank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (TargetInRange() && TargetVisible())
    {
        LookAt(Tank->GetActorLocation());
    }
}

bool ATower::TargetInRange()
{
    if (Tank)
    {
        float DistanceSqr = FVector::DistSquared2D(Tank->GetActorLocation(), GetActorLocation());
        if (DistanceSqr < FireRange * FireRange)
        {
            return true;
        }
    }
    return false;
}

bool ATower::TargetVisible()
{
    if (Tank)
    {
        FHitResult HitResult;
        GetWorld()->LineTraceSingleByChannel(
            HitResult,
            GetActorLocation(),
            Tank->GetActorLocation(),
            ECollisionChannel::ECC_Visibility);

        if (HitResult.bBlockingHit && HitResult.GetActor() == Tank)
        {
            return true;
        }
    }
    return false;
}