#include "HankGameMode.h"
#include "HankCharacter.h"
#include "HankController.h"
#include "Components/BoxComponent.h"
#include "UObject/UnrealTypePrivate.h"


AHankGameMode::AHankGameMode()
{
    PrimaryActorTick.bCanEverTick = true;


    // Initialize variables in constructor
    RenderDistance = 10; // Set initial render distance here
}

void AHankGameMode::BeginPlay()
{
    if (HankCharacterClassOne != nullptr && HankCharacterClassTwo != nullptr)
    {
        // Spawn the first Blueprint instance
        AHankCharacter* PlayerOnePawn = GetWorld()->SpawnActor<AHankCharacter>(HankCharacterClassOne, /*Location*/ FVector(0, 0, 0), /*Rotation*/ FRotator(0));

        // Spawn the second Blueprint instance
        AHankCharacter* PlayerTwoPawn = GetWorld()->SpawnActor<AHankCharacter>(HankCharacterClassTwo, /*Location*/ FVector(100, 0, 0), /*Rotation*/ FRotator(0));

        // Get the player controller
        AHankController* PlayerController = Cast<AHankController>(GetWorld()->GetFirstPlayerController());
        if (PlayerController)
        {
            // Assign the pawns to the controller
            PlayerController->SetPlayerOnePawn(PlayerOnePawn);
            PlayerController->SetPlayerTwoPawn(PlayerTwoPawn);
        }
    }
}



// MAP GEN

void AHankGameMode::StartTiles()
{
    for (int i = 0; i < RenderDistance; i++)
    {
        CreateTile();
    }
}

void AHankGameMode::PopTile()
{
    if (PieceStack.Num() > 0)
    {
        AActor* PieceToPop = PieceStack[0];
        PieceStack.RemoveAt(0);
        PieceToPop->Destroy();
    }
}

void AHankGameMode::CreateTile()
{

    AActor* NewTile = GetWorld()->SpawnActor<AActor>(Tile_Base, NextPiece.GetLocation(), NextPiece.Rotator());
    if (NewTile)
    {
        UArrowComponent* NextTransform = Cast<UArrowComponent>(NewTile->GetComponentByClass(UArrowComponent::StaticClass()));

        if (NextTransform)
            NextPiece = NextTransform->GetComponentTransform();
        
    }

    PieceStack.Add(NewTile);
    //PopulateTile(NewTile);
}




void AHankGameMode::SetSetCoinsOnNextTile(bool bNewValue)
{
    SetCoinsOnNextTile = bNewValue;
}




// Fetch a tile at Random
TSubclassOf<AActor> AHankGameMode::GetTile()
{
    return Tile_Base;
}




void AHankGameMode::Increment()
{
    PopTile();
    CreateTile();
}
