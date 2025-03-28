// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanksGameMode.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;

    // ...
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
    Super::BeginPlay();
    Health = MaxHealth;
    GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamge);
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // ...
}

void UHealthComponent::TakeDamge(AActor *DamagedActor, float Damage, const UDamageType *DamageType, class AController *InstigatedBy, AActor *DamageCauser)
{
    Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);
    UE_LOG(LogTemp, Warning, TEXT("%s TakeDamge of %f. Current Health: %f"), *DamagedActor->GetName(), Damage, Health);

    if (Health <= 0)
    {
        if (AToonTanksGameMode *GameMode = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
        {
            GameMode->ActorDied(GetOwner());
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Health Component has no reference to GameMode"));
        }
    }
}