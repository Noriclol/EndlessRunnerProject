// Fill out your copyright notice in the Description page of Project Settings.


#include "MapData.h"

void MapData::BreakStreak()
{
	dodged_rows = 0;
}

MapData::MapData(FVector pos)
{
	newPosition.SetLocation(pos);
}

MapData::~MapData()
{
}
