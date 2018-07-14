// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
#include "EnemyMovement.h"
#include "GameFramework/Pawn.h"
#include "Enemy.generated.h"

UENUM()
enum class EEnemyState : uint8
{
	MOVE,
	AIM,
	SHOOT
};

UCLASS()
class INVERSIONFPS_API AEnemy : public APawn
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* CollisionBox;

public:
	// Sets default values for this pawn's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
		USkeletalMeshComponent* Mesh = nullptr;
	
	UPROPERTY(VisibleAnywhere)
		UEnemyMovement* Movement;
	
	EEnemyState EnemyState;
};
