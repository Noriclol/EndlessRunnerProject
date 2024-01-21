#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"

#include "HankGameMode.generated.h"


/**
 * GameMode class to specify pawn and playercontroller
 * also holding the map generation stuff
 */
UCLASS()
class HANKRUNNER_API AHankGameMode : public AGameModeBase
{
	GENERATED_BODY()


public:
	class AGameCamera* camera;
	class AHankController* playerController;

	class AMapGeneration* mapGeneration;


private:
	AHankGameMode();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void SpawnPawns();
	UFUNCTION(BlueprintCallable)
	void SpawnMap();

	void IncrementLaneOne();
	void IncrementLaneTwo();


public:

	
	// Pawn classes to spawn
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	TSubclassOf<class AHankCharacter> HankCharacterClassOne;

	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	TSubclassOf<class AHankCharacter> HankCharacterClassTwo;
	
	
	// Camera class to spawn
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	TSubclassOf<class AGameCamera> GameCameraClass;

	
	// Camera class to spawn
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	TSubclassOf<class AMapGeneration> mapGenerationClass;

};
