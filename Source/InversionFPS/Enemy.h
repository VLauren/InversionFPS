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
	IDLE,
	MOVE_RIGHT,
	MOVE_LEFT,
	MOVE_FORWARD,
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

	void GenerateShoot(FVector Location, FRotator Rotation);

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = EnemyConfig)
		TSubclassOf<class AActor> Projectile;

	UPROPERTY(VisibleAnywhere)
		USkeletalMeshComponent* Mesh = nullptr;
	
	UPROPERTY(VisibleAnywhere)
		class UEnemyMovement* Movement;

	UPROPERTY(EditDefaultsOnly, Category = EnemyConfig)
		bool Black;
	
	EEnemyState EnemyState;

	static const float MOVEMENT_SPEED;
	static const float DISTANCE_TO_START;
	static const float MOVE_TIME;

	float timeCounter;

	AInversionFPSCharacter* Player;

	bool shoot;
};
