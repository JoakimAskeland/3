// Fill out your copyright notice in the Description page of Project Settings.

#include "CharGhost.h"
#include "GameFramework/PlayerInput.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraActor.h"
#include "Bullet.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Engine/Engine.h"
#include "Components/CapsuleComponent.h" 
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/WidgetComponent.h"

// Sets default values
ACharGhost::ACharGhost()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CharGhostMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharGhostMesh")); //skeletal
	//SetRootComponent(UCapsuleComponent); 

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	//CurrentVelocity = FVector(0.f);
	MaxSpeed = 100.f;


	//SpringArm
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArm->bDoCollisionTest = false;
	SpringArm->SetUsingAbsoluteRotation(true);

	SpringArm->SetRelativeRotation(FRotator(-30.f, 0.f, 0.f));
	SpringArm->TargetArmLength = 1200.f;
	SpringArm->bEnableCameraLag = false;
	SpringArm->CameraLagSpeed = 5.f;

	SpringArm->SetupAttachment(CharGhostMesh);


	//Camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->bUsePawnControlRotation = false; // Rotate camera based on controller
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	bUseControllerRotationYaw = false;

	SpringArm->bUsePawnControlRotation = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = true;
	SpringArm->bInheritRoll = false;

	// Set size for collision capsule
	GetCapsuleComponent()->SetCapsuleSize(48.f, 105.f);

	/*WidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComp"));
	WidgetComp->SetupAttachment(CharGhostMesh);*/

	// Don't rotate when the controller rotates. Let that just affect camera
	/*bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;*/

	// Set our turn rates for input
	/*BaseTurnRate = 65.f;
	BaseLookUpRate = 65.f;*/

	// Configure Character Movement
	//GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input (where it is facing)
	//GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.f, 0.0f); // Character moves at this RotationRate

	/*UCharacterMovementComponent* const MovementComponent = GetCharacterMovement();
	if (MovementComponent)
	{
		MovementComponent->bOrientRotationToMovement = true;
		MovementComponent->bUseControllerDesiredRotation = false;
	}

	GetCharacterMovement()->bOrientRotationToMovement = true;*/

}

// Called when the game starts or when spawned
void ACharGhost::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MovementMode = MOVE_Flying;

	/*if (HUDOverlayAsset)
	{
		HUDOverlay = CreateWidget<UUserWidget>(this, HUDOverlayAsset);
	}

	HUDOverlay->AddToViewport();
	HUDOverlay->SetVisibility(ESlateVisibility::Visible);*/

}

// Called every frame
void ACharGhost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//LerpPitch = FMath::FInterpTo(LerpPitch, Pitch, DeltaTime, 5.f);
	//LerpRoll = FMath::FInterpTo(LerpRoll, Roll, DeltaTime, 5.f);
	//SetActorRotation(FRotator(LerpPitch, 0.f, LerpRoll));
	///*SRotation = FRotator::ZeroRotator;*/

	//FVector CurrentLocation = GetActorLocation();


}

// Called to bind functionality to input
void ACharGhost::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ACharGhost::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ACharGhost::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ACharGhost::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ACharGhost::LookUpAtRate);

	PlayerInputComponent->BindAction("Shoot", EInputEvent::IE_Pressed, this, &ACharGhost::Shoot);
	//PlayerInputComponent->BindAction("MouseLeft", EInputEvent::IE_Pressed, this, &ACharGhost::Shoot);

	PlayerInputComponent->BindAction("Reload", EInputEvent::IE_Pressed, this, &ACharGhost::Reload);
	//PlayerInputComponent->BindAction("MouseRight", EInputEvent::IE_Pressed, this, &ACharGhost::Reload);

}


void ACharGhost::MoveForward(float Value)
{
	//CurrentVelocity.X = FMath::Clamp(value, -5.f, 5.f) * MaxSpeed;  //Moves CharGhost forward or backwards. 5 is the speed of movement, if it is to be changed it needs to be done both here and in Unreal (Engine, Input)

	//FVector Direction = Set //GetActorRotation();
	/*AddMovementInput(Direction, value);
	AddMovementInput*/

	//if ((Controller != nullptr) && (Value != 0.0f))
	//{
	//	// Find out which way is forward
	//	const FRotator Rotation = Controller->GetControlRotation();
	//	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	//	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	//	AddMovementInput(Direction, Value);
	//}

	FVector Direction = GetActorForwardVector();
	AddMovementInput(Direction, Value);

	//if (Controller != nullptr && Value > 0.0f)
	//{
	//	Pitch = 25.f;
	//	// find out which way is forward
	//	const FRotator PitchRotation(0.f, 0.f, 0.f);
	//	//UE_LOG(LogTemp, Warning, TEXT("Roll: %f"), Value);
	//	const FVector Direction = FRotationMatrix(PitchRotation).GetUnitAxis(EAxis::X);
	//	AddMovementInput(Direction, Value);
	//}

	//if (Controller != nullptr && Value < 0.0f)
	//{
	//	Pitch = -25.f;
	//	const FRotator PitchRotation(0.f, 0.f, 0.f);
	//	const FVector Direction = FRotationMatrix(PitchRotation).GetUnitAxis(EAxis::X);
	//	AddMovementInput(Direction, Value);
	//}

	//if (Controller != nullptr && Value == 0.0f)
	//{
	//	Pitch = 0.f;
	//	const FRotator PitchRotation(0.f, 0.f, 0.f);
	//	const FVector Direction = FRotationMatrix(PitchRotation).GetUnitAxis(EAxis::X);
	//	AddMovementInput(Direction, Value);
	//}


}

void ACharGhost::MoveRight(float Value)
{
	//CurrentVelocity.Y = FMath::Clamp(value, -5.f, 5.f) * MaxSpeed;  //Moves CharGhost left or right. 5 is the speed of movement, if it is to be changed it needs to be done both here and in Unreal (Engine, Input)

	//FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	//AddMovementInput(Direction, value);

	if (Value)
	{
		AddActorLocalRotation(FRotator(0, Value, 0)); 
	}

	//if ((Controller != nullptr) && (Value != 0.0f))
	//{
	//	// Find out which way is forward
	//	const FRotator Rotation = Controller->GetControlRotation();
	//	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	//	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	//	AddMovementInput(Direction, Value);
	//}

}

void ACharGhost::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ACharGhost::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ACharGhost::Shoot()
{
	if (Ammo > 0) {
		Ammo--;
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Ammo : !"), FString::FromInt(Ammo)); 
		GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::White, FString::Printf(TEXT("Ammo :  %d "), Ammo));


		UWorld* World = GetWorld();
		if (World)
		{
			FVector Location = GetActorLocation();
			//150cm ahead of actor the bullet will be spawn 
			World->SpawnActor<AActor>(ActorToSpawn, Location + FVector(250.f, 0.f, 0.f), GetActorRotation());
			UGameplayStatics::PlaySound2D(World, ShootingSound, 1.f, 1.f, 0.f, 0);

		}
		if (Ammo == 0)
		{
			GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Red, FString::Printf(TEXT("No ammo Reload %d "), Ammo));

		}
	}



	UE_LOG(LogTemp, Warning, TEXT("Shooting"));
}

void ACharGhost::Reload()
{
	if (Ammo < 10)
	{
		Ammo = 10;
		UWorld* NewWorld = GetWorld();
		GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Green, FString::Printf(TEXT("Reloaded")));
	}
}

