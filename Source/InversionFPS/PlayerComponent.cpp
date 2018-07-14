
#include "PlayerComponent.h"
#include "References.h"
#include "Runtime/CoreUObject/Public/UObject/UObjectIterator.h"
#include "Runtime/Engine/Classes/Components/MeshComponent.h"
#include "Runtime/Engine/Classes/GameFramework/Pawn.h"
#include "PlayerProjectile.h"

bool UPlayerComponent::Black = false;
UPlayerComponent* UPlayerComponent::Instance = nullptr;

UPlayerComponent::UPlayerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	GunOffset = FVector(100.0f, 0.0f, 10.0f);
}

void UPlayerComponent::BeginPlay()
{
	Super::BeginPlay();

	Instance = this;

	AActor* Owner = GetOwner();
	UInputComponent* InputComponent = Owner->InputComponent;
	if (InputComponent != NULL)
	{
		InputComponent->BindAction("Fire", IE_Pressed, this, &UPlayerComponent::OnFire);
		InputComponent->BindAction("Invert", IE_Pressed, this, &UPlayerComponent::OnInvert);
	}
}

void UPlayerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UPlayerComponent::OnFire()
{
	UWorld* const World = GetWorld();
	if (World != NULL && ProjectileBlack != nullptr && ProjectileWhite != nullptr)
	{
		// World->SpawnActor<APlayerProjectile>(Projectile, GetOwner()->GetActorLocation(), GetOwner()->GetActorRotation());

		const FRotator SpawnRotation = ((APawn*)GetOwner())->GetControlRotation();
		const FVector SpawnLocation = GetOwner()->GetActorLocation() + SpawnRotation.RotateVector(GunOffset);

		if (Black)
			World->SpawnActor<APlayerProjectile>(ProjectileBlack, SpawnLocation, SpawnRotation);
		else
			World->SpawnActor<APlayerProjectile>(ProjectileWhite, SpawnLocation, SpawnRotation);
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("Proyectil sin asignar en el blueprint del jugador"));
}

void UPlayerComponent::OnInvert()
{
	if (AReferences::Instance->MatBlack != nullptr && AReferences::Instance->MatWhite != nullptr)
	{
		for (TObjectIterator<UMeshComponent> Itr; Itr; ++Itr)
		{
			TArray<UMaterialInterface*> arr = Itr->GetMaterials();
			for (int i = 0; i < 2; i++)
			{
				if (Itr->GetMaterial(i))
				{
					if (Itr->GetMaterial(i) == AReferences::Instance->MatWhite)
						Itr->SetMaterial(i, AReferences::Instance->MatBlack);
					else if (Itr->GetMaterial(i) == AReferences::Instance->MatBlack)
						Itr->SetMaterial(i, AReferences::Instance->MatWhite);
				}
			}
		}

		Black = !Black;
	}
}
