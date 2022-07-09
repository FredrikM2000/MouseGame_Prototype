// Fill out your copyright notice in the Description page of Project Settings.


#include "Mass.h"
#include "Components/BoxComponent.h"
#include "MouseGame_Prototype/Rock.h"


AMass::AMass()
{
    Pickup = CreateDefaultSubobject<UBoxComponent>(TEXT("PickupBox"));
    Pickup->SetupAttachment(RootComponent);
}

void AMass::BeginPlay()
{
    Super::BeginPlay();

    //This is here because there is a bug if you have it in constuctor
    Pickup->OnComponentBeginOverlap.AddDynamic(this, &AMass::OnOverlapPickup);//When something overlaps the box, this function is called
    Pickup->SetGenerateOverlapEvents(false);
}

void AMass::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Interact"), IE_Pressed, this, &AMass::Interact);
	PlayerInputComponent->BindAction(TEXT("UnInteract"), IE_Released, this, &AMass::UnInteract);
}

void AMass::Interact()
{
    Super::Interact();

    Pickup->SetGenerateOverlapEvents(true);//Box can now detect overlaps
}

void AMass::UnInteract()
{
    Super::UnInteract();

    Pickup->SetGenerateOverlapEvents(false);//Box can no longer detect overlaps
}

void AMass::OnOverlapPickup(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
    UE_LOG(LogTemp, Warning, TEXT("Overlap with %s"), *OtherActor->GetName());
    
    if(OtherActor->IsA(ARock::StaticClass()))
    {
        Rock = Cast<ARock>(OtherActor);

        OtherActor->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("AttachRock"));//Attaches the Rock to the AttachRock socket in the Cone mesh

        UE_LOG(LogTemp, Warning, TEXT("Picked up a %s"), *Rock->GetName());
    }
}