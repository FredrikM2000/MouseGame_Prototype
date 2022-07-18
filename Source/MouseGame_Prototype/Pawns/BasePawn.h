// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DefaultPawn.h"
#include "BasePawn.generated.h"

class UCapsuleComponent;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class MOUSEGAME_PROTOTYPE_API ABasePawn : public ADefaultPawn
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABasePawn();

		// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Switch1();//Switch to Pawn Other1
	void Switch2();//Switch to Pawn Other2

	virtual void Interact();//On Press button
	virtual void UnInteract();//On Release button

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Switch")
	ABasePawn* Other1;

	UPROPERTY(EditAnywhere, Category = "Switch")
	ABasePawn* Other2;


};
