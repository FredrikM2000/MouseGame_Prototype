// Fill out your copyright notice in the Description page of Project Settings.


#include "MouseGame_Prototype/Pawns/BasePawn.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Switch1"), IE_Pressed, this, &ABasePawn::Switch1);
	PlayerInputComponent->BindAction(TEXT("Switch2"), IE_Pressed, this, &ABasePawn::Switch2);
}

void ABasePawn::Switch1()
{
	if(Other1 && GetController())//If Other1 is not nullptr and Controller exists
	{
		AController* temp = GetController();
		if(temp)
		{
			//Switch controll from current pawn to pawn Other1
			temp->UnPossess();
			temp->Possess(Other1);
		}
	}
}

void ABasePawn::Switch2()
{
	if(Other2 && GetController())//If Other2 is not nullptr and Controller exists
	{
		AController* temp = GetController();
		if(temp)
		{
			//Switch controll from current pawn to pawn Other2
			temp->UnPossess();
			temp->Possess(Other2);
		}
	}
}

void ABasePawn::Interact(){}//Currently not in use
void ABasePawn::UnInteract(){}//Currently not in use

