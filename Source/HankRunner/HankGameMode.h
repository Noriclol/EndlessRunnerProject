#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"

#include "HankGameMode.generated.h"


/**
 * 
 */
UCLASS()
class HANKRUNNER_API AHankGameMode : public AGameModeBase
{
	GENERATED_BODY()


private:
	AHankGameMode();



// CHARACTER
private:



// MAPGEN

	FTransform NextPiece = FTransform();
	TArray<AActor*> PieceStack;


	void PopTile();
	void CreateTile();
	//void PopulateTile(const AActor* NewTile) const;
	//UBoxComponent* FindEndOfTileCollider(AActor* Tile);

	//


	TSubclassOf<AActor> GetTile();

public:


	UPROPERTY(EditDefaultsOnly)
	float CoinSpacing;

	UPROPERTY(VisibleAnywhere)
	int RenderDistance;

	//TileReferences

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> Tile_Base;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> Tile_Turn_L;


	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> Tile_Turn_R;


	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> Tile_Turn_Jump;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> Obstacle;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> Coin;


;	UPROPERTY(BlueprintReadWrite, Category = "Coin Settings")
	bool SetCoinsOnNextTile;

	UFUNCTION(BlueprintCallable, Category = "Coin Settings")
	void SetSetCoinsOnNextTile(bool bNewValue);
	
	//UFUNCTION(BlueprintCallable)
	//void SpawnCoinRow(const FTransform& SpawnTransform) const;
	
	//UFUNCTION(BlueprintCallable)
	//void SpawnObstacle(const FTransform& SpawnTransform) const;

	UFUNCTION(BlueprintCallable)
	void Increment();

	UFUNCTION(BlueprintCallable)
	void StartTiles();
};
