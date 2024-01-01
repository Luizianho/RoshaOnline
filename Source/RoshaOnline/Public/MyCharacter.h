// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/KismetMathLibrary.h"

#include "MyCharacter.generated.h"

UCLASS()
class ROSHAONLINE_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	FVector CameraLocation;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	FRotator CameraRotation;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Ring")
	class USkeletalMeshComponent* Ring;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Amulet")
	class USkeletalMeshComponent* Amulet;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Tools")
	class USkeletalMeshComponent* Tools;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Head")
	class USkeletalMeshComponent* Head;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Hands")
	class USkeletalMeshComponent* Hands;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Legs")
	class USkeletalMeshComponent* Legs;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Feet")
	class USkeletalMeshComponent* Feet;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ShieldSlot")
	class USkeletalMeshComponent* ShieldSlot;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "WeaponSlot")
	class USkeletalMeshComponent* WeaponSlot;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Slot1")
	class USkeletalMeshComponent* Slot1;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Slot2")
	class USkeletalMeshComponent* Slot2;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Slot3")
	class USkeletalMeshComponent* Slot3;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void MoveForward(float Value);
	void MoveRight(float Value);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
