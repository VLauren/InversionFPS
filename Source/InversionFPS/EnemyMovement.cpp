
#include "EnemyMovement.h"
#include "Enemy.h"
#include "Runtime/Engine/Public/EngineUtils.h"
#include "InversionFPSCharacter.h"

void UEnemyMovement::BeginPlay()
{
	Super::BeginPlay();
	for (TActorIterator<AInversionFPSCharacter> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		Player = *ActorItr;
	}
}

void UEnemyMovement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AEnemy* Enemy;
	Enemy = (AEnemy*)GetOwner();

	if (Enemy->EnemyState == EEnemyState::IDLE)
		direction = FVector::ZeroVector;
	if (Enemy->EnemyState == EEnemyState::AIM)
	{
		float NewYaw = (Player->GetActorLocation() - GetActorLocation()).Rotation().Yaw;
		FRotator NewRotation = FRotator::MakeFromEuler(FVector(0, 0, NewYaw));

		GetOwner()->SetActorRotation(FMath::Lerp(GetOwner()->GetActorRotation(), NewRotation, 0.1f));

		direction = FVector::ZeroVector;
	}
	if (Enemy->EnemyState == EEnemyState::MOVE_RIGHT)
	{
		direction = FRotator(0, 90, 0).RotateVector(Player->GetActorLocation() - GetActorLocation()).GetSafeNormal();
		direction.Z = 0;
	}
	if (Enemy->EnemyState == EEnemyState::MOVE_LEFT)
	{
		direction = FRotator(0, -90, 0).RotateVector(Player->GetActorLocation() - GetActorLocation()).GetSafeNormal();
	}
	if (Enemy->EnemyState == EEnemyState::MOVE_FORWARD)
	{
		direction = (Player->GetActorLocation() - GetActorLocation()).GetSafeNormal();
	}
	if (Enemy->EnemyState == EEnemyState::SHOOT)
	{
		direction = FVector::ZeroVector;
	}

	FVector movementThisFrame = direction * DeltaTime * AEnemy::MOVEMENT_SPEED;
	if (!movementThisFrame.IsNearlyZero())
	{
		FHitResult Hit;

		// Movimiento
		SafeMoveUpdatedComponent(movementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);

		// Si chocamos con algo, me deslizo sobre el
		if (Hit.IsValidBlockingHit())
			SlideAlongSurface(movementThisFrame, 1.f - Hit.Time, Hit.Normal, Hit);

		// Rotacion
		FRotator TargetRotation = direction.Rotation();
		GetOwner()->SetActorRotation(FMath::Lerp(GetOwner()->GetActorRotation(), TargetRotation, 0.1f));

		// Rotacion de la malla
		// FRotator TargetRotation = movementThisFrame.Rotation() + StartMeshRotation;
		// CurrentRotation = FMath::Lerp(CurrentRotation, TargetRotation, 0.1f);

		// if(ProvisionalMesh != nullptr)
		// ProvisionalMesh->SetRelativeRotation(CurrentRotation);
		// if (Mesh != nullptr)
			// Mesh->SetRelativeRotation(CurrentRotation);
	}
}
