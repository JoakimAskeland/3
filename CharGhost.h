// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "CharGhost.generated.h"

UCLASS()
class COMP3_API ACharGhost : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharGhost();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharGhostMesh")
		USkeletalMeshComponent* CharGhostMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharGhostMesh")
		USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharGhostMesh")
		UCameraComponent* Camera;

	// Base Turn rates to scale turning functions for the camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

	UPROPERTY(EditAnywhere, Category = "Character Movement")
		float MaxSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharGhostMesh")
		int Ammo = 10;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> ActorToSpawn; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerMesh")
		USoundBase* ShootingSound = nullptr;

	/*UPROPERTY()
	class UWidgetComponent* WidgetComp;*/

	////Reference to the UMG asset in the editor
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	//	TSubclassOf<class UUserWidget> HUDOverlayAsset;

	////Variable to hold the widget after creating it
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	//	UUserWidget* HUDOverlay;

	float Pitch = 0.f;
	float Roll = 0.f;

	float LerpPitch = 0.f;
	float LerpRoll = 0.f;


private:
	// Called for Forward/Backward movement input
	void MoveForward(float Value); 

	// Called for side to side movement input
	void MoveRight(float Value);

	// Called via input to turn at a given rate
	// @param Rate This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	void TurnAtRate(float Rate);

	// Called via input to look up/down at a given rate
	// @param Rate This is a normalized rate, i.e. 1.0 means 100% of esired look up/down rate
	void LookUpAtRate(float Rate);

	void Shoot();
	void Reload();


	//FVector CurrentVelocity;

};
