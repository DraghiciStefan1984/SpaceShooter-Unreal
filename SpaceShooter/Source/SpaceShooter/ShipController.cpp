// Fill out your copyright notice in the Description page of Project Settings.

#include "ShipController.h"
#include "EnemyController.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "Runtime/Engine/Classes/Components/InputComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
// Sets default values
AShipController::AShipController()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	collisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	collisionBox->SetGenerateOverlapEvents(true);
	collisionBox->OnComponentBeginOverlap.AddDynamic(this, &AShipController::OnOverlap);
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
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AShipController::OnShoot);
	PlayerInputComponent->BindAction("Restart", IE_Pressed, this, &AShipController::OnRestart).bExecuteWhenPaused = true;
}

void AShipController::MoveX(float axisValue)
{
	currentVelocity.X = axisValue * 100.0f;
}

void AShipController::MoveY(float axisValue)
{
	currentVelocity.Y = axisValue * 100.0f;
}

void AShipController::OnShoot()
{
	UWorld* world = GetWorld();

	if (world) 
	{
		FVector location = GetActorLocation();
		world->SpawnActor<ABulletController>(bullet_BP, location, FRotator::ZeroRotator);
	}
}

void AShipController::OnRestart()
{
	if (died)
	{
		UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
	}
}

void AShipController::OnOverlap(UPrimitiveComponent * overlapComponent, AActor * otherActor, UPrimitiveComponent * otherComponent, int32 otherBodyIndex, bool bFromSweep, const FHitResult & sweepResult)
{
	if (otherActor->IsA(AEnemyController::StaticClass()))
	{
		died = true;
		this->SetActorHiddenInGame(true);
		((ASpaceShooterGameMode*)GetWorld()->GetAuthGameMode())->OnGameOver();
		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}
}

