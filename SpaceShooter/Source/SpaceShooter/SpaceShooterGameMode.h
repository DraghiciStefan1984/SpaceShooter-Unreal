// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "EnemyController.h"
#include "SpaceShooterGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SPACESHOOTER_API ASpaceShooterGameMode : public AGameMode
{
	GENERATED_BODY()



	float min_interval = 0.5f;
	float max_interval = 2.0f;
	float time_to_min_interval = 30.0f;

protected:
	int score = 0;

public:
	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<class AEnemyController> enemy_BP;

	float enemyTimer;
	float gameTimer;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
