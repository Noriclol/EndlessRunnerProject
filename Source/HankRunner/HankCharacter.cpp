#include "HankCharacter.h"


AHankCharacter::AHankCharacter()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    // Set size for collision capsule
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

}



void AHankCharacter::BeginPlay()
{
    Super::BeginPlay();
}



void AHankCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    //SetActorLocation(GetActorLocation() + FVector(playerSpeed, 0.0f, 0.0f));
    //if (!hasDied)
    //    playerSpeed += 0.001f;
}



void AHankCharacter::StopMoving()
{
    playerSpeed = 0;
    hasDied = true;
}

void AHankCharacter::Jump()
{
    Super::Jump();
}

void AHankCharacter::LeftRight(float Value)
{
    if (Value != 0.0f)
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("EEEEEEEEEEEEE"));
        }
        AddMovementInput(GetActorRightVector(), Value);
    }
}

void AHankCharacter::Die()
{
	hasDied = true;
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("DEAD"));
	}
}

bool AHankCharacter::LooseLife()
{
    return true;
}

void AHankCharacter::PickupCoin()
{
    coins ++;
}

