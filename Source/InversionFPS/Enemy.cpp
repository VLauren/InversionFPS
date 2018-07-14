// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy.h"
#include "Runtime/Engine/Public/EngineUtils.h"

const float AEnemy::MOVEMENT_SPEED = 200.0f;
const float AEnemy::DISTANCE_TO_START = 1700.0f;
const float AEnemy::MOVE_TIME = 2;

// Sets default values
AEnemy::AEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->InitBoxExtent(FVector(50, 50, 100));
	CollisionBox->bShouldUpdatePhysicsVolume = true;
	CollisionBox->bCheckAsyncSceneOnMove = false;
	CollisionBox->SetCanEverAffectNavigation(false);
	CollisionBox->bDynamicObstacle = true;
	RootComponent = CollisionBox;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	if (Mesh != nullptr)
	{
		Mesh->MeshComponentUpdateFlag = EMeshComponentUpdateFlag::AlwaysTickPose;
		Mesh->bCastDynamicShadow = true;
		Mesh->bAffectDynamicIndirectLighting = true;
		Mesh->PrimaryComponentTick.TickGroup = TG_PrePhysics;
		Mesh->SetupAttachment(CollisionBox);
		static FName MeshCollisionProfileName(TEXT("CharacterMesh"));
		Mesh->SetCollisionProfileName(MeshCollisionProfileName);
		Mesh->bGenerateOverlapEvents = false;
		Mesh->SetCanEverAffectNavigation(false);
	}

	Movement = CreateDefaultSubobject<UEnemyMovement>(TEXT("Movement"));
	Movement->UpdatedComponent = RootComponent;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	for (TActorIterator<AInversionFPSCharacter> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		Player = *ActorItr;
	}

	EnemyState = EEnemyState::IDLE;
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	timeCounter += DeltaTime;

	if (EnemyState == EEnemyState::IDLE)
	{
		// UE_LOG(LogTemp, Warning, TEXT("Dist: %f"), FVector::Dist(Player->GetActorLocation(), GetActorLocation()));

		if (FVector::Dist(Player->GetActorLocation(), GetActorLocation()) < DISTANCE_TO_START)
		{
			timeCounter = 0;
			EnemyState = EEnemyState::AIM;
		}
	}
	else if (EnemyState == EEnemyState::AIM)
	{
		if (timeCounter >= MOVE_TIME)
		{
			timeCounter = 0;
			int32 r = FMath::RandRange(0, 2);

			if(r == 0)
				EnemyState = EEnemyState::MOVE_FORWARD;
			else if(r == 1)
				EnemyState = EEnemyState::MOVE_LEFT;
			else if(r == 2)
				EnemyState = EEnemyState::MOVE_RIGHT;
		}
	}
	else
	{
		if (timeCounter >= MOVE_TIME)
		{
			timeCounter = 0;
			EnemyState = EEnemyState::AIM;

			UE_LOG(LogTemp, Warning, TEXT("DISPARO"));
		}
	}

}


