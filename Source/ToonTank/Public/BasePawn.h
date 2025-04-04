// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANK_API ABasePawn : public APawn
{
    GENERATED_BODY()

public:
    // Sets default values for this pawn's properties
    ABasePawn();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

    void LookAt(const FVector &Target);

    void Shoot();

    virtual void HandleDestruction();

    inline bool IsDead() const { return bIsDead; }

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Base Pawn", meta = (AllowPrivateAccess = true))
    class UCapsuleComponent *CapsuleComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Base Pawn", meta = (AllowPrivateAccess = true))
    UStaticMeshComponent *BaseMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Base Pawn", meta = (AllowPrivateAccess = true))
    UStaticMeshComponent *TurretMesh;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = true))
    TSubclassOf<AActor> ProjectileClass;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Base Pawn", meta = (AllowPrivateAccess = true))
    USceneComponent *ProjectileSpawnPoint;

    bool bIsDead = false;
};
