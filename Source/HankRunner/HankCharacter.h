#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "HankGameMode.h"


#include "HankCharacter.generated.h"

/**
 * base class for the player characters
 */
UCLASS()
class HANKRUNNER_API AHankCharacter : public ACharacter
{
	GENERATED_BODY()

	// VARIABLES

private:



	float x_position;
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float playerSpeed = 5.0f;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool hasDied = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int lives = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int coins = 0;

protected:


	// Collider
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collider", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleCollider;





	// FUNCTIONS

public:

	// Input Functions
	virtual void Jump() override;

	void Die();

	bool LooseLife();

	void PickupCoin();

	UFUNCTION(BlueprintCallable)
	void LeftRight(float Value);

protected:

	virtual void BeginPlay() override;

	AHankCharacter();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void StopMoving();
};
