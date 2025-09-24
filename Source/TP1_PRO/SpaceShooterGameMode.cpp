// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShooterGameMode.h"
#include "Destroyable.h"
#include "Engine/World.h"


ASpaceShooterGameMode::ASpaceShooterGameMode()
{
	
}


void ASpaceShooterGameMode::BeginPlay()
{
	Super::BeginPlay();

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	UWorld* World = GetWorld();
	
	for (int i = 0; i < NumberToSpawn; ++i)
	{
		FVector SpawnLocation = FVector(
			FMath::RandRange(1000,Radius)*(FMath::RandBool() ? -1 : 1),
			FMath::RandRange(1000,Radius)*(FMath::RandBool() ? -1 : 1),
			0);

		FRotator SpawnRotation = FRotator(0,rand()%360,0);
		
		World->SpawnActor<ADestroyable>(
			DestroyableClass,
			SpawnLocation,
			SpawnRotation,
			SpawnParameters
		);
		
	}
}
