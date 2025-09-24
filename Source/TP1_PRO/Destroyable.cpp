// Fill out your copyright notice in the Description page of Project Settings.


#include "Destroyable.h"
#include "Player/Ship.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADestroyable::ADestroyable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DestroyableMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	DestroyableMovement->ProjectileGravityScale = 0;
	DestroyableMovement->bAutoActivate = false;
	DestroyableMovement->MaxSpeed = 5000;
	DestroyableMovement->bShouldBounce = true;
	
}

// Called when the game starts or when spawned
void ADestroyable::BeginPlay()
{
	Super::BeginPlay();
	Hp = rand()%4+1;	
}

// Called every frame
void ADestroyable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADestroyable::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);


	if (OtherActor->ActorHasTag("Ship"))
	{
		AShip* Ship = Cast<AShip>(OtherActor);
		if (Ship)
		{
			Ship->LoseHp();
			Destroy();
		};
	}
	
	if (OtherActor->ActorHasTag("Bullet"))
	{
		
		Hp -= 1;

	}
	if (Hp <= 0)
	{
		AShip* Ship = Cast<AShip>(UGameplayStatics::GetActorOfClass(GetWorld(), AShip::StaticClass()));
		if (Ship)
		{
			Ship->AddScore();
		}
		Destroy();
	}
}

