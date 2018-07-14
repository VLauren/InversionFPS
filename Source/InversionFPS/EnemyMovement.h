// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InversionFPSCharacter.h"
#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "EnemyMovement.generated.h"

/**
 * 
 */
UCLASS()
class INVERSIONFPS_API UEnemyMovement : public UPawnMovementComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	
	AActor* Player;
	
private:
	FVector direction;
};
