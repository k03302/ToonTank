// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "BasePawn.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectile::AProjectile()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
    SetRootComponent(ProjectileMesh);
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
    Super::BeginPlay();
    ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AProjectile::OnHit(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit)
{
    if (!OtherActor || OtherActor == this || OtherActor == GetOwner())
        return;

    if (ABasePawn *BasePawnHitted = Cast<ABasePawn>(OtherActor))
    {
        UE_LOG(LogTemp, Warning, TEXT("projectile from %s hitted %s"), *GetName(), *BasePawnHitted->GetName());

        AController *Controller = GetInstigatorController();

        UGameplayStatics::ApplyDamage(BasePawnHitted, 20.f, Controller, this, TSubclassOf<UDamageType>(UDamageType::StaticClass()));
    }

    Destroy();
}