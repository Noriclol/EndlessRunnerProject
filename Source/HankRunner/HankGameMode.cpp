#include "HankGameMode.h"

#include "Components/BoxComponent.h"
#include "UObject/UnrealTypePrivate.h"


AHankGameMode::AHankGameMode()
{
    PrimaryActorTick.bCanEverTick = true;


    // Initialize variables in constructor
    RenderDistance = 10; // Set initial render distance here
}



// MAP GEN

void AHankGameMode::StartTiles()
{
    for (int i = 0; i < RenderDistance; i++)
    {
        CreateTile();
    }
}

//void AHankGameMode::SpawnCoinRow(const FTransform& SpawnTransform) const
//{
//	const int32 NumCoins = FMath::RandRange(3, 5);
//
//    for (int32 i = 0; i < NumCoins; i++)
//    {
//        FVector CoinLocation = SpawnTransform.GetLocation() + FVector(CoinSpacing * i, 0.0f, 0.0f);
//        FTransform CoinTransform = FTransform(SpawnTransform.GetRotation(), CoinLocation, FVector::OneVector);
//        GetWorld()->SpawnActor<AActor>(Coin, CoinTransform);
//    }
//}
//
//void AHankGameMode::SpawnObstacle(const FTransform& SpawnTransform) const
//{
//    GetWorld()->SpawnActor<AActor>(Obstacle, SpawnTransform);
//}


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

//void AHankGameMode::PopulateTile(const AActor* NewTile) const
//{
//    TArray<UBoxComponent*> BoxColliders;
//    NewTile->GetComponents<UBoxComponent>(BoxColliders);
//
//    TArray<UBoxComponent*> SpawnAreaColliders;
//    for (UBoxComponent* BoxCollider : BoxColliders)
//    {
//        if (BoxCollider->GetName().Contains(TEXT("SpawnArea")))
//        {
//            SpawnAreaColliders.Add(BoxCollider);
//        }
//    }
//
//    if (SpawnAreaColliders.Num() >= 3)
//    {
//        int32 FirstIndex = FMath::RandRange(0, 2);
//        int32 SecondIndex = (FirstIndex + FMath::RandRange(1, 2)) % 3;
//
//        SpawnObstacle(SpawnAreaColliders[FirstIndex]->GetComponentTransform());
//        SpawnObstacle(SpawnAreaColliders[SecondIndex]->GetComponentTransform());
//
//        if (SetCoinsOnNextTile)
//        {
//            SpawnCoinRow(SpawnAreaColliders[2 - FirstIndex - SecondIndex]->GetComponentTransform());
//        }
//    }
//}


void AHankGameMode::SetSetCoinsOnNextTile(bool bNewValue)
{
    SetCoinsOnNextTile = bNewValue;
}


//UBoxComponent* AHankGameMode::FindEndOfTileCollider(AActor* Tile)
//{
//    TArray<UBoxComponent*> BoxColliders;
//    Tile->GetComponents<UBoxComponent>(BoxColliders);
//
//    for (UBoxComponent* BoxCollider : BoxColliders)
//    {
//        if (BoxCollider->GetName().Contains(TEXT("EndOfTile")))
//        {
//            return BoxCollider;
//        }
//    }
//
//    return nullptr;
//}





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
