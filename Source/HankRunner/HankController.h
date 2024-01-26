// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "HankController.generated.h"

/**
 * Controller for both players
 */
UCLASS()
class HANKRUNNER_API AHankController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void SetupInputComponent() override;

private:

	class AHankCharacter* PlayerOnePawn;

	class AHankCharacter* PlayerTwoPawn;

	void MovePlayerOneLeftRight(float value);
	void PlayerOneJump();

	void MovePlayerTwoLeftRight(float value);
	void PlayerTwoJump();

	void ReturnToMainMenu();

public:
	UFUNCTION(BlueprintCallable)
	void SetPlayerOnePawn(AHankCharacter* newPawn);
	UFUNCTION(BlueprintCallable)
	void SetPlayerTwoPawn(AHankCharacter* newPawn);
};
