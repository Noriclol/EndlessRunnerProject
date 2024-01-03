// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class HANKRUNNER_API MapGen
{
public:

	FTransform NextPiece = FTransform();



	TArray<AActor*> PieceStack;

	UPROPERTY(VisibleAnywhere)
	int RenderDistance;


	MapGen();
	~MapGen();
};
