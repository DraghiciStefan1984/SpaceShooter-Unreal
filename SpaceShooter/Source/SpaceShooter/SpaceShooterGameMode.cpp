// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceShooterGameMode.h"

void ASpaceShooterGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void ASpaceShooterGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	gameTimer += DeltaTime;
	enemyTimer -= DeltaTime;

	if (enemyTimer <= 0.0f)
	{
		float difficulty_percentage = FMath::Min(gameTimer / time_to_min_interval, 1.0f);
		enemyTimer = max_interval - (max_interval - min_interval) * difficulty_percentage;

		UWorld* world = GetWorld();

		if (world)
		{
			FVector location = FVector(600.0f, FMath::RandRange(-800.0f, 800.0f), 70.0f);
			world->SpawnActor<AEnemyController>(enemy_BP, location, FRotator::ZeroRotator);
		}
	}
}
