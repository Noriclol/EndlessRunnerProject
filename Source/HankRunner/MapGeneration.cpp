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


    if (mapgenerated)
        MoveMap();
        gamespeed += 0.001f;

    
    //loop through all the tiles in maps.
        for (int i = 0; i < TrackOne.Stack.Num(); i++)
        {
            AFloorTile* tile = TrackOne.Stack[i];
            //if the tile is out of bounds, pop it and create a new one
            if (tile->GetActorLocation().X < cut_off)
            {
                Increment(&TrackOne);
            }
        }
        for (int i = 0; i < TrackTwo.Stack.Num(); i++)
        {
            AFloorTile* tile = TrackTwo.Stack[i];
			//if the tile is out of bounds, pop it and create a new one
            if (tile->GetActorLocation().X < cut_off)
            {
				Increment(&TrackTwo);
			}
        }


	//if (TrackOne.Stack.Num() < RenderDistance)
	//{
	//	Increment(&TrackOne);
	//}
	//if (TrackTwo.Stack.Num() < RenderDistance)
	//{
	//	Increment(&TrackTwo);
	//}   
}

void AMapGeneration::StartTiles()
{
    for (int i = 0; i < RenderDistance; i++)
    {
        CreateTile(&TrackOne);
        CreateTile(&TrackTwo);
    }
    mapgenerated = true;
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
    if (data->firstTile) 
    {
        //place a tile at the end of the stack
        AFloorTile* NewTile = GetWorld()->SpawnActor<AFloorTile>(Tile_Base, data->newPosition.GetLocation(), data->newPosition.Rotator());
        if (NewTile) 
        {
            // Fetch the next transform from the top of the stack and spawn a new tile
            UArrowComponent* NextTransform = Cast<UArrowComponent>(data->Stack.Last()->GetComponentByClass(UArrowComponent::StaticClass()));
            if (NextTransform)
                data->newPosition = NextTransform->GetComponentTransform();
        }
        data->firstTile = false;
    }
    else 
    {
        //place a tile at the start
    }

    // Fetch the next transform from the top of the stack and spawn a new tile
    UArrowComponent* NextTransform = Cast<UArrowComponent>(data->Stack.Last()->GetComponentByClass(UArrowComponent::StaticClass()));
    if (NextTransform)
        data->newPosition = NextTransform->GetComponentTransform();

    AFloorTile* NewTile = GetWorld()->SpawnActor<AFloorTile>(Tile_Base, data->newPosition.GetLocation(), data->newPosition.Rotator());

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

    UBoxComponent* CollisionBox;

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
            else if (name.Equals(TEXT("CollisionBox")))
			{
				CollisionBox = Cast<UBoxComponent>(child);
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

void AMapGeneration::MoveMap()
{
    for (size_t i = 0; i < TrackOne.Stack.Num() ; i++)
    {
        AFloorTile* tile = TrackOne.Stack[i];
        tile->SetActorLocation(tile->GetActorLocation() + FVector(-gamespeed, 0.0f, 0.0f));
    }
    for (size_t i = 0; i < TrackOne.Stack.Num(); i++)
    {
        AFloorTile* tile = TrackTwo.Stack[i];
        tile->SetActorLocation(tile->GetActorLocation() + FVector(-gamespeed, 0.0f, 0.0f));
    }
}



void AMapGeneration::Increment(MapData* mapData)
{
    PopTile(mapData);
    CreateTile(mapData);
}