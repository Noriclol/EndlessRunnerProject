#include "HankCharacter.h"


AHankCharacter::AHankCharacter()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    // Set size for collision capsule
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);


    // camera boom
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 300.0f;
    CameraBoom->bUsePawnControlRotation = true;

    // camera
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false; 
}



void AHankCharacter::BeginPlay()
{
    Super::BeginPlay();

}



void AHankCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    SetActorLocation(GetActorLocation() + FVector(playerSpeed, 0.0f, 0.0f));
    if (!hasDiead)
        playerSpeed += 0.001f;
}



void AHankCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    //Input Setup
    //PlayerInputComponent->BindAxis("LeftRight", this, &AHankCharacter::LeftRight);
    //PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AHankCharacter::Jump);
}

void AHankCharacter::StopMoving()
{
    playerSpeed = 0;
    hasDiead = true;
}

void AHankCharacter::Jump()
{
    Super::Jump();
}

void AHankCharacter::LeftRight(float Value)
{
    if (Value != 0.0f)
    {
        UE_LOG(LogTemp, Warning, TEXT("LeftRight function called"));

        AddMovementInput(GetActorRightVector(), Value);
    }
}

