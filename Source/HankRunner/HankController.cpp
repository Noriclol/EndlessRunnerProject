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
    //if (GEngine)
    //{
    //    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("MovePlayerOneLR Called"));
    //    FString TheFloatStr = FString::SanitizeFloat(value);
    //    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, *TheFloatStr);
    //}
    if (PlayerOnePawn)
    {
        //Possess(PlayerOnePawn);
        PlayerOnePawn->LeftRight(value);
    }
}

void AHankController::PlayerOneJump()
{
    //if (GEngine)
    //{
    //    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("PlayerOne Jump Called"));
    //}
    if (PlayerOnePawn)
    {
        //Possess(PlayerOnePawn);
        PlayerOnePawn->Jump();
    }
}

void AHankController::MovePlayerTwoLeftRight(float value)
{
    //if (GEngine)
    //{
    //    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("MovePlayerTwoLR Called"));
    //    FString TheFloatStr = FString::SanitizeFloat(value);
    //    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, *TheFloatStr);
    //}
    if (PlayerTwoPawn)
    {
        //Possess(PlayerTwoPawn);
        PlayerTwoPawn->LeftRight(value);
    }
}

void AHankController::PlayerTwoJump()
{
    //if (GEngine)
    //{
    //    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("PlayerTwo Jump Called"));
    //}
    if (PlayerTwoPawn)
    {
        //Possess(PlayerTwoPawn);
        PlayerTwoPawn->Jump();
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