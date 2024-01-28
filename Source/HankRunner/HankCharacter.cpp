#include "HankCharacter.h"
#include "Kismet/GameplayStatics.h"

AHankCharacter::AHankCharacter()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    // Set size for collision capsule
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
    x_position = GetActorLocation().X;
}



void AHankCharacter::BeginPlay()
{
    Super::BeginPlay();
}



void AHankCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    SetActorLocation(FVector(x_position, GetActorLocation().Y, GetActorLocation().Z));

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
        AddMovementInput(GetActorRightVector(), Value);
    }
}

void AHankCharacter::Die()
{
	hasDied = true;

    AHankGameMode* MyGameMode = Cast<AHankGameMode>(UGameplayStatics::GetGameMode(this));

    if (MyGameMode)
    {
        MyGameMode->game_over = true;
        OnCharacterHasDied();
    }
}

bool AHankCharacter::LooseLife()
{
    lives--;
    if (lives <= 0)
    {
		Die();
		return true;
	}
    return false;
}


void AHankCharacter::PickupCoin()
{
    coins ++;
}

