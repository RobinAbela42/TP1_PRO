// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SpaceShooterGameMode.generated.h"

class ADestroyable;
/**
 * 
 */
UCLASS()
class TP1_PRO_API ASpaceShooterGameMode : public AGameModeBase
{
	GENERATED_BODY()

	public:
		ASpaceShooterGameMode();
	
	protected:  
		virtual void BeginPlay() override;


	public:
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawning")
		TSubclassOf<ADestroyable> DestroyableClass;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawning")
		int32 NumberToSpawn = 25;
	
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawning")
		int32 Radius = 15000;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawning")
		int32 MaxSpeed = 2000;
	
};