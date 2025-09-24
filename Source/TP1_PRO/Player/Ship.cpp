// Fill out your copyright notice in the Description page of Project Settings.


#include "TP1_PRO/Player/Ship.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "TP1_PRO/Destroyable.h"
#include "TP1_PRO/UI_DeathScreen.h"


// Sets default values
AShip::AShip()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	World = GetWorld();

	static ConstructorHelpers::FClassFinder<UUI_DeathScreen> DeathScreenFinder(TEXT("/Game/UI/BP_DeathScreen")); // Adjust path to your widget blueprint
	if (DeathScreenFinder.Succeeded())
	{
		DeathScreen = DeathScreenFinder.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> PauseScreenFinder(TEXT("/Game/UI/BP_PauseScreen")); // Adjust path to your widget blueprint
	if (PauseScreenFinder.Succeeded())
	{
		PauseScreen = PauseScreenFinder.Class;
	}
}

// Called when the game starts or when spawned
void AShip::BeginPlay()
{
	Super::BeginPlay();

	Speed = 1000;
	
}

// Called every frame
void AShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AShip::Shoot);
	PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &AShip::Pause);
	PlayerInputComponent->BindAxis("MoveForward", this, &AShip::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AShip::AddControllerYawInput);
}

void AShip::MoveForward(float Value)
{
	FVector DesiredVelocity = GetActorForwardVector() * Speed * Value;

	if (Value != 0)
	{
		GetCharacterMovement()->Velocity = DesiredVelocity;
	}
	else
	{
		GetCharacterMovement()->Velocity = GetActorForwardVector();
	}
}

void AShip::Shoot()
{
	
}

void AShip::AddScore()
{
	Score += 1;
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;



	
	if (Score%5 == 0)
	{
		ActualX = GetActorLocation().X;
		ActualY = GetActorLocation().Y;


		xmin = ActualX - 6000*1.5;
		xmax = ActualX + 6000*1.5;
		ymax = ActualY + 6000;
		ymin = ActualY - 6000;

		// UE_LOG(LogTemp, Warning, TEXT("Position X: %f Y: %f "),ActualX ,ActualY);

		
		for (int i =0; i < 5; i++)
		{

			SpawningX = ActualX;
			SpawningY = ActualY;
			// UE_LOG(LogTemp, Warning, TEXT("Actual : %f x et %f y"), SpawningX, SpawningY);
			RandomLocationOnSquare(xmin, xmax, ymin, ymax);
			// UE_LOG(LogTemp, Warning, TEXT("Il va Spawn en : %f x et %f y"), SpawningX, SpawningY);

			FVector SpawnLocation = FVector(SpawningX, SpawningY, 0);
			FRotator SpawnRotation = FRotator(0,rand()%360,0);
			
			World->SpawnActor<ADestroyable>(
				DestroyableClass,
				SpawnLocation,
				SpawnRotation,
				SpawnParameters
			);
			
			// UE_LOG(LogTemp, Warning, TEXT("Score: %d, "), Score);
			
		}

	}
}
void AShip::LoseHp()
{
	Hp -= 1;
	if (Hp <= 0)
	{
		Death();
		
	}
}

void AShip::Death()
{
	if (DeathScreen)
	{
		UUI_DeathScreen* DeathScreenInstance = CreateWidget<UUI_DeathScreen>(GetWorld(), DeathScreen);
		if (DeathScreenInstance)
		{
			DeathScreenInstance->AddToViewport();
			APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			if (PC)
			{
				FInputModeUIOnly InputMode;
				InputMode.SetWidgetToFocus(DeathScreenInstance->TakeWidget());
				InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
				PC->SetInputMode(InputMode);
				PC->bShowMouseCursor = true;
			}
		}
		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}
	
}

void AShip::Pause()
{
	if (PauseScreen)
	{
		UUserWidget* PauseScreenInstance = CreateWidget<UUserWidget>(GetWorld(), PauseScreen);
		if (PauseScreenInstance)
		{
			PauseScreenInstance->AddToViewport();
			APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			if (PC)
			{
				FInputModeUIOnly InputMode;
				InputMode.SetWidgetToFocus(PauseScreenInstance->TakeWidget());
				InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
				PC->SetInputMode(InputMode);
				PC->bShowMouseCursor = true;
			}
		}
		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}
}

void AShip::RandomLocationOnSquare(double x_min, double x_max, double y_min, double y_max)
{
	double p =  2 * (xmax - xmin) + 2 * (ymax - ymin);

	double position = FMath::RandRange(1.0, p);

	// UE_LOG(LogTemp, Warning, TEXT("Position sur le permietre : %f // Xmin : %f Xmax : %f  Ymin : %f  Ymax : %f "), position, x_min, x_max, y_min, y_max);
	
	if (position < (x_max - x_min)) {
		// Arête du bas (x_min, y_min) -> (x_max, y_min)
		SpawningX = x_min + position;
		SpawningY = y_min;
	} else if (position < (x_max - x_min + y_max - y_min)) {
		// Arête de droite (x_max, y_min) -> (x_max, y_max)
		position -= (x_max - x_min);
		SpawningX = x_max;
		SpawningY = y_min + position;
	} else if (position < (x_max - x_min + y_max - y_min + x_max - x_min)) {
		// Arête du haut (x_max, y_max) -> (x_min, y_max)
		position -= (x_max - x_min + y_max - y_min);
		SpawningX = x_max - position;
		SpawningY = y_max;
	} else {
		// Arête de gauche (x_min, y_max) -> (x_min, y_min)
		position -= (x_max - x_min + y_max - y_min + x_max - x_min);
		SpawningX = x_min;
		SpawningY = y_max - position;
	}

	// UE_LOG(LogTemp, Warning, TEXT("Perimeter  : %f //  Position: %f // X: %f Y: %f "),p, position, SpawningX, SpawningY);
	
	
}

	


