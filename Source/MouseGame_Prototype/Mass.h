// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "Mass.generated.h"

class UBoxComponent;
class ARock;

UCLASS()
class MOUSEGAME_PROTOTYPE_API AMass : public ABaseCharacter
{
	GENERATED_BODY()
	
	public:

	AMass();

	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Interact() override;//On Press button
	void UnInteract() override;//On Release button

	UFUNCTION()
	void OnOverlapPickup(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult);
	
	UPROPERTY(VisibleAnywhere, Category = "BoxComponent", meta = (AllowPrivateAccess = "true"));
	UBoxComponent* Pickup{nullptr};

private:

	ARock* Rock;

protected:
	void BeginPlay() override;
	
};
