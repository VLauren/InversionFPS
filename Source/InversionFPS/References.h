// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Runtime/Engine/Classes/Materials/Material.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "References.generated.h"

UCLASS()
class INVERSIONFPS_API AReferences : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AReferences();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	static AReferences* Instance;

	UPROPERTY(EditAnywhere)
	UMaterial* MatWhite;

	UPROPERTY(EditAnywhere)
	UMaterial* MatBlack;
	
	
};
