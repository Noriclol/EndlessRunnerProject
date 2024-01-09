// Fill out your copyright notice in the Description page of Project Settings.

#include "MapGeneration.h"

AMapGeneration::AMapGeneration()
{
	PrimaryActorTick.bCanEverTick = true;
    RenderDistance = 10;
    TrackOne = MapData(FVector(0, -400.0, 0));
    TrackTwo = MapData(FVector(0, 400.0, 0));
}



// Called when the game starts or when spawned
void AMapGeneration::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMapGeneration::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMapGeneration::StartTiles()
{



    for (int i = 0; i < RenderDistance; i++)
    {
        CreateTile(&TrackOne);
        CreateTile(&TrackTwo);
    }
}

void AMapGeneration::PopTile(MapData* data)
{
    if (data->Stack.Num() > 0)
    {
        AActor* PieceToPop = data->Stack[0];
        data->Stack.RemoveAt(0);
        PieceToPop->Destroy();
    }
}

void AMapGeneration::CreateTile(MapData* data)
{

    AActor* NewTile = GetWorld()->SpawnActor<AActor>(Tile_Base, data->newPosition.GetLocation(), data->newPosition.Rotator());
    if (NewTile)
    {
        UArrowComponent* NextTransform = Cast<UArrowComponent>(NewTile->GetComponentByClass(UArrowComponent::StaticClass()));

        if (NextTransform)
            data->newPosition = NextTransform->GetComponentTransform();

    }
    data->Stack.Add(NewTile);
    //Populate Tile?
}


void AMapGeneration::PopulateTile(AFloorTile* NewTile) 
{

    //Find the spawn points of the tile
    TArray<UBoxComponent*> boxes;
    NewTile->GetComponents<UBoxComponent>(boxes);

    UBoxComponent* Spawnpoint_Left;
    UBoxComponent* Spawnpoint_Middle;
    UBoxComponent* Spawnpoint_Right;

    for (int i = 0; i < boxes.Num(); i++)
    {
        if (boxes[i])
        {
            UActorComponent* child = boxes[i];
            FString name = child->GetName();

            if (name.Equals(TEXT("Spawnpoint_Left")))
            {
                Spawnpoint_Left = Cast<UBoxComponent>(child);
            }
            else if (name.Equals(TEXT("Spawnpoint_Middle")))
            {
                Spawnpoint_Middle = Cast<UBoxComponent>(child);
            }
            else if (name.Equals(TEXT("Spawnpoint_Right")))
            {
                Spawnpoint_Right = Cast<UBoxComponent>(child);
            }
        }
    }
    ////if all spawn points are found
    //if (Spawnpoint_Left && Spawnpoint_Middle && Spawnpoint_Right)
    //{
    //    //Spawn the obstacles. 3 cases, either the obstacles spawn on LR, LM, or MR
    //    //RANDOM 1 , 2, 3
    //    int random = FMath::RandRange(1, 3);
    //    switch (random) {
    //    case 1:
    //        //NewTile->SpawnObstacle(Spawnpoint_Left->);
    //        //NewTile->Spawn(Spawnpoint_Right);
    //        break;
    //    case 2:
    //        //NewTile->Spawn(Spawnpoint_Left);
    //        //NewTile->Spawn(Spawnpoint_Middle);
    //        break;
    //    case 3:
    //        //NewTile->Spawn(Spawnpoint_Middle);
    //        //NewTile->Spawn(Spawnpoint_Right);
    //        break;
    //    }
    //}
}

void AMapGeneration::SetSetCoinsOnNextTile(MapData* data, bool bNewValue)
{
    data->SetCoinsOnNextTile = bNewValue;
}





void AMapGeneration::Increment(MapData* mapData)
{
    PopTile(mapData);
    CreateTile(mapData);
}