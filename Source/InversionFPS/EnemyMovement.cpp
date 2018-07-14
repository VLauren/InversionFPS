
#include "EnemyMovement.h"
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

	if (Enemy->EnemyState == EEnemyState::AIM)
	{
		float NewYaw = (Player->GetActorLocation() - GetActorLocation()).Rotation().Yaw;
		FRotator NewRotation = FRotator::MakeFromEuler(FVector(0, 0, NewYaw));
		GetPawnOwner()->SetActorRotation(NewRotation);
	}
	if (Enemy->EnemyState == EEnemyState::MOVE)
	{

	}
	if (Enemy->EnemyState == EEnemyState::SHOOT)
	{

	}
}
