// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePawn.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ABasePawn::ABasePawn()
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
    SetRootComponent(CapsuleComponent);

    BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
    BaseMesh->SetupAttachment(CapsuleComponent);

    TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
    TurretMesh->SetupAttachment(BaseMesh);

    ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint"));
    ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABasePawn::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABasePawn::LookAt(const FVector &Target)
{
    FVector LookDirection = Target - GetActorLocation();
    LookDirection.Z = 0.f;
    FRotator LookRotation = LookDirection.Rotation();
    // LookRotation.Roll = 0.f;
    // LookRotation.Pitch = 0.f;

    TurretMesh->SetWorldRotation(FMath::RInterpTo(TurretMesh->GetComponentRotation(), LookRotation, GetWorld()->GetDeltaSeconds(), 2.f));
}

void ABasePawn::Shoot()
{
    UE_LOG(LogTemp, Warning, TEXT("Shoot"));
    if (ProjectileClass && ProjectileSpawnPoint)
        GetWorld()->SpawnActor<AActor>(ProjectileClass, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation());
}

void ABasePawn::HandleDestruction()
{
}