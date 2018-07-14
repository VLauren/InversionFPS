// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INVERSIONFPS_API UPlayerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class AActor> ProjectileBlack = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class AActor> ProjectileWhite = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
		FVector GunOffset;

	void OnFire();
	void OnInvert();

	static bool Black;

	static UPlayerComponent* Instance;
	
};
