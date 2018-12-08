// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BulletController.h"
#include "Runtime/Engine/Classes/GameFramework/DefaultPawn.h"
#include "Runtime/CoreUObject/Public/Templates/Casts.h"
#include "ShipController.generated.h"

UCLASS()
class SPACESHOOTER_API AShipController : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AShipController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
	UShapeComponent* collisionBox;

	UPROPERTY(EditAnywhere)
	float speed = 10.0f;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<class ABulletController> bullet_BP;

	FVector currentVelocity;

	void MoveX(float axisValue);
	void MoveY(float axisValue);
	void OnShoot();
};
