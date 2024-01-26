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

    AHankGameMode* MyGameMode = Cast<AHankGameMode>(UGameplayStatics::GetGameMode(this));

    if (MyGameMode)
    {
        if (MyGameMode->game_over)
        {
            gamespeed = 0.0f;
            return;
        }
        // MyGameMode is successfully cast and can be used here

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
    }
}

void AMapGeneration::StartTiles()
{
    //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Start Tiles Called"));
    for (int i = 0; i < RenderDistance; i++)
    {
        CreateTile(&TrackOne);
        CreateTile(&TrackTwo);
        //if (GEngine)
        //{
        //    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("CreateTilesCalled"));
        //}
    }
    mapgenerated = true;
}

void AMapGeneration::PopTile(MapData* data)
{
    if (data->Stack.Num() > 0)
    {
        AFloorTile* PieceToPop = data->Stack[0];
        data->Stack.RemoveAt(0);
        PieceToPop->DestroyTile();
    }
}

void AMapGeneration::CreateTile(MapData* data)
{

    AFloorTile* NewTile;

    if (data->firstTile) 
    {
        //place a tile at the end of the stack
        NewTile = GetWorld()->SpawnActor<AFloorTile>(Tile_Base, data->newPosition.GetLocation(), data->newPosition.Rotator());

        if (NewTile)
        {
            data->Stack.Add(NewTile);
            PopulateTile(NewTile);
        }
        data->firstTile = false;
    }
    else 
    {

        // Fetch the next transform from the top of the stack and spawn a new tile
        UArrowComponent* NextTransform = Cast<UArrowComponent>(data->Stack.Last()->GetComponentByClass(UArrowComponent::StaticClass()));
        if (NextTransform)
            data->newPosition = NextTransform->GetComponentTransform();

        NewTile = GetWorld()->SpawnActor<AFloorTile>(Tile_Base, data->newPosition.GetLocation(), data->newPosition.Rotator());
        if (NewTile)
        {
            data->Stack.Add(NewTile);
            PopulateTile(NewTile);
        }
    }

    //if (NewTile) 
    //{
    //    data->Stack.Add(NewTile);
    //    PopulateTile(NewTile);
    //    //if (mapgenerated)
    //    //    PopulateTile(NewTile);
    //}
}


FVector GetPointInBox(UBoxComponent* Box)
{
    if (!Box)
    {
        return FVector::ZeroVector; // Return a default value if Box is null
    }

    // Get the center and extents of the box
    FVector Center = Box->GetComponentTransform().GetLocation();
    FVector Extents = Box->GetScaledBoxExtent();

    // Generate a random point within the box
    float RandomX = FMath::RandRange(-Extents.X, Extents.X);
    float RandomY = FMath::RandRange(-Extents.Y, Extents.Y);
    float RandomZ = FMath::RandRange(-Extents.Z, Extents.Z);

    // Add the random offset to the center
    FVector RandomPoint = Center + FVector(RandomX, RandomY, RandomZ);

    return Center;
}


void AMapGeneration::PopulateTile(AFloorTile* NewTile) 
{
    if (!GEngine)
        return;

    //Find the spawn points of the tile
    TArray<UBoxComponent*> boxes;
    NewTile->GetComponents<UBoxComponent>(boxes);

    UBoxComponent* Spawnpoint_Left = nullptr;
    UBoxComponent* Spawnpoint_Middle = nullptr;
    UBoxComponent* Spawnpoint_Right = nullptr;

    UBoxComponent* CollisionBox = nullptr;
    //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("For Loop"));
    //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Number of boxes: ") + FString::FromInt(boxes.Num()));
    for (int i = 0; i < boxes.Num(); i++)
    {
        //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("For Loop"));
        if (boxes[i])
        {
            UActorComponent* child = boxes[i];
            FString name = child->GetName();

            if (name.Equals(TEXT("Spawnpoint_Left")))
            {
                //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Spawnpoint_Left Set"));
                Spawnpoint_Left = Cast<UBoxComponent>(child);
            }
            else if (name.Equals(TEXT("Spawnpoint_Middle")))
            {
                //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Spawnpoint_Middle Set"));
                Spawnpoint_Middle = Cast<UBoxComponent>(child);
            }
            else if (name.Equals(TEXT("Spawnpoint_Right")))
            {
                //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Spawnpoint_Right Set"));
                Spawnpoint_Right = Cast<UBoxComponent>(child);
            }
        }
    }

    //if all spawn points are found
    if (Spawnpoint_Left && Spawnpoint_Middle && Spawnpoint_Right)
    {
        //Spawn the obstacles. 3 cases, either the obstacles spawn on LR, LM, or MR
        //RANDOM 1 , 2, 3
        int random = FMath::RandRange(1, 3);
        switch (random) {
        case 1:
            //if (GEngine)
            //{
            //    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("PopulateTile Called: 1"));
            //}

            NewTile->SpawnObstacle(Spawnpoint_Left->GetComponentLocation());
            NewTile->SpawnObstacle(Spawnpoint_Right->GetComponentLocation());

            break;

        case 2:
            //if (GEngine)
            //{
            //    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("PopulateTile Called: 2"));
            //}

            NewTile->SpawnObstacle(Spawnpoint_Left->GetComponentLocation());
            NewTile->SpawnObstacle(Spawnpoint_Middle->GetComponentLocation());
            break;

        case 3:
            //if (GEngine)
            //{
            //    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("PopulateTile Called: 3"));
            //}

            NewTile->SpawnObstacle(Spawnpoint_Middle->GetComponentLocation());
            NewTile->SpawnObstacle(Spawnpoint_Right->GetComponentLocation());
            break;

        }
    }
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