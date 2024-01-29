#include "HankGameMode.h"
#include "HankCharacter.h"
#include "HankController.h"
#include "GameCamera.h"
#include "Components/BoxComponent.h"
#include "UObject/UnrealTypePrivate.h"
#include "FileHandler.h"
#include "MapGeneration.h"



AHankGameMode::AHankGameMode()
{
    PrimaryActorTick.bCanEverTick = true;

    // Initialize variables in constructor
}

void AHankGameMode::BeginPlay()
{
    PrimaryActorTick.bCanEverTick = true;
    playerController = Cast<AHankController>(GetWorld()->GetFirstPlayerController());
    game_over = false;

    if (playerController == nullptr)
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("PlayerController is null"));
        }
    }
    else 
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("PlayerController is NOT null"));
        }
    }


    // Spawn the map generation
    if (mapGenerationClass != nullptr)
    {
        mapGeneration = GetWorld()->SpawnActor<AMapGeneration>(mapGenerationClass, /*Location*/ FVector(0, 0, 0), /*Rotation*/ FRotator(0));
    }
    else
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("MapGeneration class is null"));
        }
    }

    // Spawn the camera
    if (GameCameraClass != nullptr)
    {
		camera = GetWorld()->SpawnActor<AGameCamera>(GameCameraClass, /*Location*/ FVector(-700.0, 0, 720.0), /*Rotation*/ FRotator(-30, 0, 0));
        playerController->SetViewTargetWithBlend(camera); // Specify blend parameters if needed
    }
}

void AHankGameMode::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

void AHankGameMode::SpawnPawns()
{

    //Spawn the characters
    if (HankCharacterClassOne != nullptr && HankCharacterClassTwo != nullptr)
    {
        // Spawn the first Blueprint instance
        AHankCharacter* PlayerOnePawn = GetWorld()->SpawnActor<AHankCharacter>(HankCharacterClassOne, /*Location*/ FVector(20, -400.0, 200.0), /*Rotation*/ FRotator(0));

        // Spawn the second Blueprint instance
        AHankCharacter* PlayerTwoPawn = GetWorld()->SpawnActor<AHankCharacter>(HankCharacterClassTwo, /*Location*/ FVector(20, 400.0, 200.0), /*Rotation*/ FRotator(0));

        // Get the player controller

        if (playerController)
        {
            // Assign the pawns to the controller
            playerController->SetPlayerOnePawn(PlayerOnePawn);
            playerController->SetPlayerTwoPawn(PlayerTwoPawn);
        }
    }
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Character class is null"));
		}
	}
}


FString AHankGameMode::GetHighScore()
{
    bool bOutSuccess;
    FString OutMessageInfo;
    return FileHandler::ReadStringFromFile("C:/Temp/HighScore.txt", bOutSuccess, OutMessageInfo);
}


void AHankGameMode::IncrementLaneOne()
{
    mapGeneration->Increment(&mapGeneration->TrackOne);
}

void AHankGameMode::FloatObstacleOne()
{
    mapGeneration->FloatObstacle(&mapGeneration->TrackOne);
}

void AHankGameMode::FloatObstacleTwo()
{
    mapGeneration->FloatObstacle(&mapGeneration->TrackOne);
}

void AHankGameMode::BreakStreakOne()
{
    mapGeneration->TrackOne.BreakStreak();
}

void AHankGameMode::BreakStreakTwo()
{
    mapGeneration->TrackTwo.BreakStreak();
}


void AHankGameMode::IncrementLaneTwo()
{
    mapGeneration->Increment(&mapGeneration->TrackTwo);
}




