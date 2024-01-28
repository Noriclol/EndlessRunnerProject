// Fill out your copyright notice in the Description page of Project Settings.


#include "HankController.h"
#include "HankCharacter.h"
#include "Kismet/GameplayStatics.h"

void AHankController::SetupInputComponent()
{
	Super::SetupInputComponent();
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("SetupInputController HankController"));
    }

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
    AHankGameMode* MyGameMode = Cast<AHankGameMode>(UGameplayStatics::GetGameMode(this));

    if (MyGameMode)
    {
        if (PlayerOnePawn && !MyGameMode->game_over)
        {
            //Possess(PlayerOnePawn);
            PlayerOnePawn->LeftRight(value);
        }
    }
}

void AHankController::PlayerOneJump()
{
    AHankGameMode* MyGameMode = Cast<AHankGameMode>(UGameplayStatics::GetGameMode(this));

    if (MyGameMode)
    {
        if (PlayerOnePawn && !MyGameMode->game_over)
        {
            //Possess(PlayerOnePawn);
            PlayerOnePawn->Jump();
        }
    }
}

void AHankController::MovePlayerTwoLeftRight(float value)
{
    AHankGameMode* MyGameMode = Cast<AHankGameMode>(UGameplayStatics::GetGameMode(this));

    if (MyGameMode)
    {
        if (PlayerTwoPawn && !MyGameMode->game_over)
        {
            PlayerTwoPawn->LeftRight(value);
        }
    }

}

void AHankController::PlayerTwoJump()
{
    AHankGameMode* MyGameMode = Cast<AHankGameMode>(UGameplayStatics::GetGameMode(this));

    if (MyGameMode)
    {
        if (PlayerTwoPawn && !MyGameMode->game_over)
        {
            PlayerTwoPawn->Jump();
        }
    }
}


void AHankController::SetPlayerTwoPawn(AHankCharacter* newPawn)
{
    if (newPawn != nullptr)
        PlayerTwoPawn = newPawn;
}

void AHankController::SetPlayerOnePawn(AHankCharacter* newPawn)
{
    if (newPawn != nullptr)
        PlayerOnePawn = newPawn;
}