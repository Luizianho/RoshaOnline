// Fill out your copyright notice in the Description page of Project Settings.


#include "RoshaCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
ARoshaCharacter::ARoshaCharacter()
{

	//SetCameraLocation 
	SetCameraLocation = FVector(0.f, 0.f, 70.f);
	SetCameraRotation = FRotator(-55.f, 0.f, 0.f);

	//SpringArm settings
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->SetRelativeLocation(SetCameraLocation);
	CameraBoom->SetRelativeRotation(SetCameraRotation);
	CameraBoom->TargetArmLength = 1400.f;

	//Camera settings
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Player Ring
	Ring = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Ring"));
	Ring->SetupAttachment(GetMesh());

	// Player Amulet
	Amulet = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Amulet"));
	Amulet->SetupAttachment(GetMesh());

	// Player Tools
	Tools = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Tools"));
	Tools->SetupAttachment(GetMesh());

	// Player Head
	Head = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Head"));
	Head->SetupAttachment(GetMesh());

	// Player Hands
	Hands = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Hands"));
	Hands->SetupAttachment(GetMesh());

	// Player Legs
	Legs = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Legs"));
	Legs->SetupAttachment(GetMesh());

	// Player Feet
	Feet = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Feet"));
	Feet->SetupAttachment(GetMesh());

	// Player ShieldSlot
	ShieldSlot = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ShieldSlot"));
	ShieldSlot->SetupAttachment(GetMesh());

	// Player WeaponSlot
	WeaponSlot = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponSlot"));
	WeaponSlot->SetupAttachment(GetMesh());

	// Player Slot1
	Slot1 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Slot1"));
	Slot1->SetupAttachment(GetMesh());

	// Player Slot2
	Slot2 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Slot2"));
	Slot2->SetupAttachment(GetMesh());

	// Player Slot3
	Slot3 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Slot3"));
	Slot3->SetupAttachment(GetMesh());

}

// Called when the game starts or when spawned
void ARoshaCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARoshaCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARoshaCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ARoshaCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ARoshaCharacter::MoveRight);

}

void ARoshaCharacter::MoveForward(float Value)
{
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}


void ARoshaCharacter::MoveRight(float Value)
{
	// find out which way is forward
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

