// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * Mapdata struct containing all the data for the map
 */
class HANKRUNNER_API MapData
{
public:

	FTransform newPosition = FTransform();

	TArray<AActor*> Stack;

	TArray<AActor*> Obstacles;

	TArray<AActor*> Collectables;

	bool SetCoinsOnNextTile;

	MapData(FVector positionOne = FVector(0, 0, 0));
	~MapData();
};
