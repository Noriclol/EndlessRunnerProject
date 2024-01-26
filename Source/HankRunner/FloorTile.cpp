// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorTile.h"
#include "Obstacle.h"
#include "Coin.h"

// Sets default values
AFloorTile::AFloorTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}



// Called when the game starts or when spawned
void AFloorTile::BeginPlay()
{
	Super::BeginPlay();
	
}

//void AFloorTile::BeginDestroy()
//{
//    // Perform any additional cleanup needed for Obstacles and Coins
//    for (AObstacle* obstacle : Obstacles)
//    {
//        if (obstacle)
//        {
//            // For example, detach the obstacle if it's attached to something
//            obstacle->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
//        }
//    }
//
//    for (ACoin* coin : Coins)
//    {
//        if (coin)
//        {
//            // Similarly, detach the coin if needed
//            coin->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
//        }
//    }
//
//    // Clear the arrays
//    Obstacles.Empty();
//    Coins.Empty();
//}

// Called every frame
void AFloorTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFloorTile::DestroyTile()
{
    for (AObstacle* obstacle : Obstacles)
    {
        if (obstacle)
        {
            obstacle->Destroy();
        }
    }

    for (ACoin* coin : Coins)
    {
        if (coin)
        {
            coin->Destroy();
        }
    }

    Obstacles.Empty();
    Coins.Empty();

    // Now destroy the floor tile itself
    Destroy();
}

void AFloorTile::MoveTile(float DeltaTime, float speed)
{
    SetActorLocation(GetActorLocation() + FVector(speed, 0.0f, 0.0f));
}

void AFloorTile::SpawnObstacle(FVector SpawnLocation)
{
    if (!Obstacle) // Check if the Obstacle class is set
    {
		UE_LOG(LogTemp, Warning, TEXT("ObstacleClass not set in FloorTile"));
		return;
	}

    //if (GEngine)
    //{
    //    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("FloorTile: Obstacle Spawn called"));
    //}

    AObstacle* obstacle = GetWorld()->SpawnActor<AObstacle>(Obstacle, SpawnLocation, FRotator::ZeroRotator);
    if (!obstacle)
    {
		UE_LOG(LogTemp, Warning, TEXT("Failed to spawn obstacle"));
	}
    else {
        obstacle->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
        Obstacles.Add(obstacle);
    }

}

void AFloorTile::SpawnCoins(FVector SpawnLocation)
{
    if (!Coin) // Check if the Coin class is set
    {
        UE_LOG(LogTemp, Warning, TEXT("CoinClass not set in FloorTile"));
        return;
    }

    // Spawn parameters
    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;
    SpawnParams.Instigator = GetInstigator();

    // Spawn the coin
    ACoin* SpawnedCoin = GetWorld()->SpawnActor<ACoin>(Coin, SpawnLocation, FRotator::ZeroRotator, SpawnParams);
    if (!SpawnedCoin)
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to spawn coin"));
    }
}


