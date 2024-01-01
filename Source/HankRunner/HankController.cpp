// Fill out your copyright notice in the Description page of Project Settings.


#include "HankController.h"
#include "HankCharacter.h"
#include "Kismet/GameplayStatics.h"

void AHankController::SetupInputComponent()
{
	Super::SetupInputComponent();

    InputComponent->BindAxis("PlayerOneLeftRight", this, &AHankController::MovePlayerOneLeftRight);
    InputComponent->BindAction("PlayerOneJump", IE_Pressed, this, &AHankController::PlayerOneJump);

    // Bind the axis and actions for Player Two
    InputComponent->BindAxis("PlayerTwoLeftRight", this, &AHankController::MovePlayerTwoLeftRight);
    InputComponent->BindAction("PlayerTwoJump", IE_Pressed, this, &AHankController::PlayerTwoJump);

    InputComponent->BindAction("BackToMenu", IE_Pressed, this, &AHankController::ReturnToMainMenu);

}

void AHankController::ReturnToMainMenu()
{
	UGameplayStatics::OpenLevel(GetWorld(), "MainMenu");
}




void AHankController::MovePlayerOneLeftRight(float value)
{
    if (PlayerOnePawn)
    {
        PlayerOnePawn->LeftRight(value);
    }
}

void AHankController::PlayerOneJump()
{
    if (PlayerOnePawn)
    {
        PlayerOnePawn->Jump();
    }
}

void AHankController::MovePlayerTwoLeftRight(float value)
{
    if (PlayerTwoPawn)
    {
        PlayerTwoPawn->LeftRight(value);
    }
}

void AHankController::PlayerTwoJump()
{
    if (PlayerTwoPawn)
    {
        PlayerTwoPawn->Jump();
    }
}


void AHankController::SetPlayerTwoPawn(AHankCharacter* pawn)
{
    if (pawn != nullptr)
    {
        PlayerTwoPawn = pawn;

        // Optionally, you can also possess the pawn immediately
        // Possess(PlayerOnePawn);

        // Or perform any other initialization required for the pawn
    }
}

void AHankController::SetPlayerOnePawn(AHankCharacter* pawn)
{
    if (pawn != nullptr)
    {
        PlayerOnePawn = pawn;

        // Optionally, you can also possess the pawn immediately
        // Possess(PlayerOnePawn);

        // Or perform any other initialization required for the pawn
    }
}