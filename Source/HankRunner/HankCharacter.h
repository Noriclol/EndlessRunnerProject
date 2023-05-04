#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "HankCharacter.generated.h"

UCLASS()
class HANKRUNNER_API AHankCharacter : public ACharacter
{
	GENERATED_BODY()

protected:





	//Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

	// Collider
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collider", meta = (AllowPrivateAccess = "true"))
		class UCapsuleComponent* CapsuleCollider;


	virtual void BeginPlay() override;

public:

	AHankCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UFUNCTION(BlueprintCallable)
	void StopMoving();

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float playerSpeed = 5.0f;
	bool hasDiead = false;

public:

	// Input Functions


	virtual void Jump() override;

	UFUNCTION(BlueprintCallable)
	void LeftRight(float Value);


};
