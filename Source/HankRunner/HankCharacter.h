#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"

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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float playerSpeed = 5.0f;

	bool hasDied = false;
	int lives = 3;
	int coins = 0;

public:



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
