// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FloorTile.h"
/**
 * Mapdata struct containing all the data for the map
 */
class HANKRUNNER_API MapData
{
public:

	FTransform newPosition = FTransform();

	TArray<AFloorTile*> Stack;

	int dodged_rows = 0;

	bool SetCoinsOnNextTile;
	bool firstTile = true;

	void BreakStreak();

	MapData(FVector positionOne = FVector(0, 0, 0));
	~MapData();
};
