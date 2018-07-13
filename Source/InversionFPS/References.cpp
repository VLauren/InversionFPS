
#include "References.h"

AReferences* AReferences::Instance;

AReferences::AReferences()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AReferences::BeginPlay()
{
	Super::BeginPlay();
	
	Instance = this;
}

void AReferences::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

