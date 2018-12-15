// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "EnemyController.h"
#include "SpaceShooterGameMode.h"
#include "BulletController.generated.h"

UCLASS()
class SPACESHOOTER_API ABulletController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABulletController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UShapeComponent* rootBox;

	UPROPERTY(EditAnywhere)
	float speed = 500.0f;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* overlapComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult);
};
