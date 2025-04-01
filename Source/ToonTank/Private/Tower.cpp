// Fill out your copyright notice in the Description page of Project Settings.

#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

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

    if (!Tank->IsDead() && TargetInRange() && TargetVisible())
    {
        LookAt(Tank->GetActorLocation());
        CheckShootCondition();
    }
}

bool ATower::TargetInRange()
{
    if (Tank)
    {
        float DistanceSqr = FVector::DistSquared2D(Tank->GetActorLocation(), GetActorLocation());
        return DistanceSqr < FireRange * FireRange;
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

        return HitResult.bBlockingHit && HitResult.GetActor() == Tank;
    }
    return false;
}

void ATower::CheckShootCondition()
{

    if (Tank && TargetInRange() && TargetVisible() && GetWorld()->GetTimeSeconds() - LastFireTime > FireRate)
    {
        Shoot();
        LastFireTime = GetWorld()->GetTimeSeconds();
    }
}

void ATower::HandleDestruction()
{
    Super::HandleDestruction();
}