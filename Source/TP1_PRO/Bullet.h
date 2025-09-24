// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class TP1_PRO_API ABullet : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FTimerHandle TimerHandle;
	
public:	
	// Sets default values for this actor's properties
	ABullet();

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	void DestroySelf();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	class UProjectileMovementComponent* BulletComponent;

};
