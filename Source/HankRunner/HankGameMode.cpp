#include "HankGameMode.h"
#include "HankCharacter.h"
#include "HankController.h"
#include "GameCamera.h"
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

    AGameCamera* camera;
    AHankController* playerController;

    playerController = Cast<AHankController>(GetWorld()->GetFirstPlayerController());


    if (playerController == nullptr)
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("PlayerController is null"));
        }
        return;
    }


    // Spawn the camera
    if (GameCameraClass != nullptr)
    {
		camera = GetWorld()->SpawnActor<AGameCamera>(GameCameraClass, /*Location*/ FVector(-700.0, 0, 720.0), /*Rotation*/ FRotator(-30, 0, 0));
        playerController->SetViewTargetWithBlend(camera); // Specify blend parameters if needed
    }


    //Spawn the characters
    if (HankCharacterClassOne != nullptr && HankCharacterClassTwo != nullptr)
    {
        // Spawn the first Blueprint instance
        AHankCharacter* PlayerOnePawn = GetWorld()->SpawnActor<AHankCharacter>(HankCharacterClassOne, /*Location*/ FVector(20, -400.0, 200.0), /*Rotation*/ FRotator(0));


        // Spawn the first Blueprint instance
        //AHankCharacter* PlayerOnePawn = GetWorld()->SpawnActor<AHankCharacter>(HankCharacterClassOne, /*Location*/ FVector(200, 0, 200.0), /*Rotation*/ FRotator(0));
         
        // Spawn the second Blueprint instance
        AHankCharacter* PlayerTwoPawn = GetWorld()->SpawnActor<AHankCharacter>(HankCharacterClassTwo, /*Location*/ FVector(20, 400.0, 200.0), /*Rotation*/ FRotator(0));

        // Get the player controller
        
        if (playerController)
        {
            // Assign the pawns to the controller
            playerController->SetPlayerOnePawn(PlayerOnePawn);
            playerController->SetPlayerTwoPawn(PlayerTwoPawn);
        }

        AActor* NewTileR = GetWorld()->SpawnActor<AActor>(Tile_Base, FVector(0, 400.0, 0), NextPiece.Rotator());
        AActor* NewTileL = GetWorld()->SpawnActor<AActor>(Tile_Base, FVector(0, -400.0, 0), NextPiece.Rotator());
        //CreateTile();

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
