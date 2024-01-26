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
        //if (GEngine)
        //{
        //    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("EEEEEEEEEEEEE"));
        //}
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
        // MyGameMode is successfully cast and can be used here
    }
    else
    {
        // Handle the case where the GameMode is not of type AHankGameMode
    }


	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("DEAD"));
	}
}


void AHankCharacter::PickupCoin()
{
    coins ++;
}

