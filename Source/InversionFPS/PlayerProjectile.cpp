
#include "PlayerProjectile.h"
#include "Enemy.h"

APlayerProjectile::APlayerProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->InitSphereRadius(30);
	CollisionSphere->bShouldUpdatePhysicsVolume = true;
	CollisionSphere->bCheckAsyncSceneOnMove = false;
	CollisionSphere->SetCanEverAffectNavigation(false);
	CollisionSphere->bDynamicObstacle = true;
	RootComponent = CollisionSphere;
}

void APlayerProjectile::BeginPlay()
{
	Super::BeginPlay();

	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &APlayerProjectile::OnOverlap);
}

void APlayerProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalOffset(FVector(DeltaTime * 1500, 0, 0));
}

void APlayerProjectile::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if (OtherComp != nullptr)
	{
		// UE_LOG(LogTemp, Warning, TEXT("ALGO! %s"), *OtherComp->GetOwner()->GetName());

		if (OtherComp->GetOwner()->GetClass()->IsChildOf<AEnemy>())
		{
			UE_LOG(LogTemp, Warning, TEXT("Colision con enemigo"));
			Destroy();
		}
	}
}


