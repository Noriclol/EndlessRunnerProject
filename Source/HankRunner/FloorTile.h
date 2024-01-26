// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloorTile.generated.h"

UCLASS()
class HANKRUNNER_API AFloorTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloorTile();

	//virtual ~AFloorTile();

	UPROPERTY(EditDefaultsOnly, Category = "MapGen")
	TSubclassOf<class AObstacle> Obstacle;

	UPROPERTY(EditDefaultsOnly, Category = "MapGen")
	TSubclassOf<class ACoin> Coin;

	TArray<AObstacle*> Obstacles;

	TArray<ACoin*> Coins;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//virtual void BeginDestroy() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void DestroyTile();

	void MoveTile(float DeltaTime, float speed);

	void SpawnObstacle(FVector SpawnLocation);

	void SpawnCoins(FVector SpawnLocation);

};
