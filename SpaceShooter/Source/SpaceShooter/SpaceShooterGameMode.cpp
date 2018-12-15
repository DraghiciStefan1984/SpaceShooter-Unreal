// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceShooterGameMode.h"
#include "EnemyController.h"

void ASpaceShooterGameMode::BeginPlay()
{
	Super::BeginPlay();

	ChangeMenuWidget(startingWidgetClass);
	((UGameWidget*)currentWidget)->Load();
}

void ASpaceShooterGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	gameTimer += DeltaTime;
	enemyTimer -= DeltaTime;
	UWorld* world = GetWorld();

	if (enemyTimer <= 0.0f)
	{
		float difficulty_percentage = FMath::Min(gameTimer / time_to_min_interval, 1.0f);
		enemyTimer = max_interval - (max_interval - min_interval) * difficulty_percentage;

		UE_LOG(LogTemp, Warning, TEXT("enemyTimer=%d"), enemyTimer);
		UE_LOG(LogTemp, Warning, TEXT("gameTimer=%d"), gameTimer);

		if (world)
		{
			FVector location = FVector(600.0f, FMath::RandRange(-600.0f, 600.0f), 70.0f);
			world->SpawnActor<AEnemyController>(EnemyBP, location, FRotator::ZeroRotator);
		}
	}
}

void ASpaceShooterGameMode::ChangeMenuWidget(TSubclassOf<UUserWidget> widgetClass)
{
	if (currentWidget != nullptr)
	{
		currentWidget->RemoveFromViewport();
		currentWidget = nullptr;
	}

	if (widgetClass != nullptr)
	{
		currentWidget = CreateWidget<UUserWidget>(GetWorld(), widgetClass);

		if (currentWidget != nullptr)
		{
			currentWidget->AddToViewport();
		}
	}
}

void ASpaceShooterGameMode::IncrementScore()
{
	score += 100;
	((UGameWidget*)currentWidget)->SetScore(score);
}

void ASpaceShooterGameMode::OnGameOver()
{
	((UGameWidget*)currentWidget)->OnGameOver();
}
