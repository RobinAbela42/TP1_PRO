// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TP1_PRO/Destroyable.h"
#include "Ship.generated.h"

UCLASS()
class TP1_PRO_API AShip : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShip();
	


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUI_DeathScreen> DeathScreen;
	
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UUserWidget> PauseScreen;

	
	UWorld* World;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawning")
	TSubclassOf<ADestroyable> DestroyableClass;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABullet> BulletActor;

	UPROPERTY(EditAnywhere)
	float Speed;

	float ActualX, ActualY, xmin, ymin, xmax, ymax;

	float SpawningX, SpawningY;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Score = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Hp = 3;
	
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawning")
	// int SpawnRadius = 8000;
	//
	// UPROPERTY(EditAnywhere, BlueprintReadWrite);	
	// int NbrOfSpawn = 75;
	//
	void MoveForward(float Value);
	void Shoot();

	void AddScore();
	void LoseHp();

	void Pause();
	void Death();

	void RandomLocationOnSquare(double xmin, double xmax, double ymin, double ymax);
	
};
