// Fill out your copyright notice in the Description page of Project Settings.

#include "BulletController.h"
#include "EnemyController.h"

// Sets default values
ABulletController::ABulletController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	rootBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	rootBox->SetGenerateOverlapEvents(true);
	rootBox->OnComponentBeginOverlap.AddDynamic(this, &ABulletController::OnOverlap);
}

// Called when the game starts or when spawned
void ABulletController::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABulletController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector newLocation = GetActorLocation();
	newLocation.X += speed * DeltaTime;
	SetActorLocation(newLocation);

	if (newLocation.X > 600.0f)
	{
		this->Destroy();
	}
}

void ABulletController::OnOverlap(UPrimitiveComponent * overlapComponent, AActor * otherActor, UPrimitiveComponent * otherComponent, int32 otherBodyIndex, bool bFromSweep, const FHitResult & sweepResult)
{
	if (otherActor->IsA(AEnemyController::StaticClass()))
	{ 
		otherActor->Destroy();
		this->Destroy();
		((ASpaceShooterGameMode*)GetWorld()->GetAuthGameMode())->IncrementScore();
	}
}

