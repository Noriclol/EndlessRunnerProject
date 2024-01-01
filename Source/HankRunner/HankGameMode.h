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

protected:
	virtual void BeginPlay() override;

// CHARACTER
private:


// MAPGEN

	FTransform NextPiece = FTransform();
	TArray<AActor*> PieceStack;


	void PopTile();
	void CreateTile();

	TSubclassOf<AActor> GetTile();

public:


	UPROPERTY(EditDefaultsOnly)
	float CoinSpacing;

	UPROPERTY(VisibleAnywhere)
	int RenderDistance;

	
	
	// Pawn classes to spawn
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	TSubclassOf<class AHankCharacter> HankCharacterClassOne;

	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	TSubclassOf<class AHankCharacter> HankCharacterClassTwo;
	
	
	
	
	//TileReferences

	UPROPERTY(EditDefaultsOnly, Category = "MapGen")
	TSubclassOf<AActor> Tile_Base;

	UPROPERTY(EditDefaultsOnly, Category = "MapGen")
	TSubclassOf<AActor> Obstacle;

	UPROPERTY(EditDefaultsOnly, Category = "MapGen")
	TSubclassOf<AActor> Coin;


;	UPROPERTY(BlueprintReadWrite, Category = "Coin Settings")
	bool SetCoinsOnNextTile;

	UFUNCTION(BlueprintCallable, Category = "Coin Settings")
	void SetSetCoinsOnNextTile(bool bNewValue);
	
	UFUNCTION(BlueprintCallable)
	void Increment();

	UFUNCTION(BlueprintCallable)
	void StartTiles();
};
