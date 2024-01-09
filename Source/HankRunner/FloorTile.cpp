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

// Called every frame
void AFloorTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFloorTile::SpawnObstacle(FVector& SpawnLocation)
{
	//GetWorld->SpawnActor<AActor>(Obstacle, SpawnLocation, FRotator::ZeroRotator);
}

void AFloorTile::SpawnCoins(FVector& SpawnLocation)
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


