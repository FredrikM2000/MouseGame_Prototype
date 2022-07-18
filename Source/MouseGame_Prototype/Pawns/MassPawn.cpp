// Fill out your copyright notice in the Description page of Project Settings.


#include "MouseGame_Prototype/Pawns/MassPawn.h"
#include "Components/BoxComponent.h"
#include "MouseGame_Prototype/Rock.h"

AMassPawn::AMassPawn()
{
    Pickup = CreateDefaultSubobject<UBoxComponent>(TEXT("PickupBox"));
    Pickup->SetupAttachment(RootComponent);
}

void AMassPawn::BeginPlay()
{
    Super::BeginPlay();

    //This is here because there is a bug if you have it in constuctor
    Pickup->OnComponentBeginOverlap.AddDynamic(this, &AMassPawn::OnOverlapPickup);//When something overlaps the box, this function is called
    Pickup->SetGenerateOverlapEvents(false);
}

void AMassPawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Interact"), IE_Pressed, this, &AMassPawn::Interact);
	PlayerInputComponent->BindAction(TEXT("Interact"), IE_Released, this, &AMassPawn::UnInteract);
}

void AMassPawn::Interact()
{
    Super::Interact();

    Pickup->SetGenerateOverlapEvents(true);//Box can now detect overlaps
}

void AMassPawn::UnInteract()
{
    Super::UnInteract();

    Pickup->SetGenerateOverlapEvents(false);//Box can no longer detect overlaps
}

void AMassPawn::OnOverlapPickup(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
    UE_LOG(LogTemp, Warning, TEXT("Overlap with %s"), *OtherActor->GetName());
    
    if(OtherActor->IsA(ARock::StaticClass()))
    {
        Rock = Cast<ARock>(OtherActor);

        OtherActor->AttachToComponent(
            Mesh, 
            FAttachmentTransformRules::SnapToTargetIncludingScale, 
            FName("AttachRock")
            );//Attaches the Rock to the AttachRock socket in the Cone mesh

        UE_LOG(LogTemp, Warning, TEXT("Picked up a %s"), *Rock->GetName());
    }
}