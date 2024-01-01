// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraLocation = FVector(0.f, 0.f, -70.f);
	CameraRotation = FRotator(-52.f, 0.f, 0.f);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetCapsuleComponent());
	CameraBoom->TargetArmLength = 1000.f;
	CameraBoom->bUsePawnControlRotation = true;

	CameraBoom->SetRelativeLocation(CameraLocation);
	CameraBoom->SetRelativeRotation(CameraRotation);
	CameraBoom->bInheritPitch = false;
	CameraBoom->bInheritYaw = false;
	CameraBoom->bInheritRoll = false;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;

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

	MasterComponent = GetMesh();
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyCharacter::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	Ring->SetMasterPoseComponent(MasterComponent);
	Amulet->SetMasterPoseComponent(MasterComponent);
	Tools->SetMasterPoseComponent(MasterComponent);
	Head->SetMasterPoseComponent(MasterComponent);
	Hands->SetMasterPoseComponent(MasterComponent);
	Legs->SetMasterPoseComponent(MasterComponent);
	Feet->SetMasterPoseComponent(MasterComponent);
	ShieldSlot->SetMasterPoseComponent(MasterComponent);
	WeaponSlot->SetMasterPoseComponent(MasterComponent);
	Slot1->SetMasterPoseComponent(MasterComponent);
	Slot2->SetMasterPoseComponent(MasterComponent);
	Slot3->SetMasterPoseComponent(MasterComponent);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (PlayerInputComponent)
	{
		PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
		PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);
	}

}

void AMyCharacter::MoveForward(float Value)
{
	
	if (Controller != nullptr && Value != 0.f)
	{
		const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
		const FVector Direction(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X));
		AddMovementInput(Direction, Value);
	}
}

void AMyCharacter::MoveRight(float Value)
{
	if (Controller != nullptr && Value != 0.f)
	{
		const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
		const FVector Direction(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y));
		AddMovementInput(Direction, Value);
	}
}

