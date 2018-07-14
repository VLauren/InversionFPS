
#include "EnemyProjectile.h"
#include "InversionFPSCharacter.h"

AEnemyProjectile::AEnemyProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->InitSphereRadius(50);
	CollisionSphere->bShouldUpdatePhysicsVolume = true;
	CollisionSphere->bCheckAsyncSceneOnMove = false;
	CollisionSphere->SetCanEverAffectNavigation(false);
	CollisionSphere->bDynamicObstacle = true;
	RootComponent = CollisionSphere;
}

void AEnemyProjectile::BeginPlay()
{
	Super::BeginPlay();

	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AEnemyProjectile::OnOverlap);
}

void AEnemyProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalOffset(FVector(DeltaTime * 500, 0, 0));
}

void AEnemyProjectile::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if (OtherComp != nullptr)
	{
		// UE_LOG(LogTemp, Warning, TEXT("ALGO! %s"), *OtherComp->GetOwner()->GetName());

		if (OtherComp->GetOwner()->GetClass()->IsChildOf<AInversionFPSCharacter>())
		{
			UE_LOG(LogTemp, Warning, TEXT("Colision con jugador"));
			Destroy();
		}

		// Ganar
		// if (CollectedItems >= ItemsToCollect)
		// {
			// CollectedItems = 0;
			// UGameplayStatics::OpenLevel(this, TEXT("/Game/Level/WinScreen"));
		// }
		// else
			// Destroy();
	}
}
