// Fill out your copyright notice in the Description page of Project Settings.

#include "ShipController.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "Runtime/Engine/Classes/Components/InputComponent.h"

// Sets default values
AShipController::AShipController()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	collisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AShipController::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AShipController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!currentVelocity.IsZero())
	{
		FVector newLocation = GetActorLocation() + speed * currentVelocity*DeltaTime;
		SetActorLocation(newLocation);
	}
}

// Called to bind functionality to input
void AShipController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveX", this, &AShipController::MoveX); 
	PlayerInputComponent->BindAxis("MoveY", this, &AShipController::MoveY);
}

void AShipController::MoveX(float axisValue)
{
	currentVelocity.X = axisValue * 100.0f;
}

void AShipController::MoveY(float axisValue)
{
	currentVelocity.X = axisValue * 100.0f;
}

