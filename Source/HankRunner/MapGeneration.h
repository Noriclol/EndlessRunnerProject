// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "MapData.h"
#include "FloorTile.h"
#include "Obstacle.h"
#include "HankGameMode.h"
#include "Kismet/GameplayStatics.h"

#include "MapGeneration.generated.h"

/**
 * Map Generation class that handles the generation of the map lanes
 */
UCLASS()
class HANKRUNNER_API AMapGeneration : public AActor
{
	GENERATED_BODY()
	
public:	

	UPROPERTY(VisibleAnywhere)
	int RenderDistance;

	UPROPERTY(EditDefaultsOnly, Category = "MapGen")
	TSubclassOf<class AFloorTile> Tile_Base;


	float cut_off = -1700.0f;
	float gamespeed = 5.0f;
	float gamespeed_increment = 0.002f;


	bool gameover = false;
	bool mapgenerated = false;

	int dodged_rows_required = 5;

	// MapData
	MapData TrackOne;
	MapData TrackTwo;


	AMapGeneration();
	// Sets default values for this actor's properties

	void StartTiles();

	void NewStartTiles();

	void PopTile(MapData* data);
	void CreateTile(MapData* data);
	void PopulateTile(AFloorTile* NewTile);
	void Increment(MapData* data);

	void SetSetCoinsOnNextTile(MapData* data, bool bNewValue);


	void FloatObstacle(MapData* data);

	void MoveMap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
