// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable.h"

#include "MissionPossibleCharacter.h"

// Sets default values for this component's properties
UInteractable::UInteractable()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInteractable::BeginPlay()
{
	Super::BeginPlay();
	
	GetOwner()->OnActorBeginOverlap.AddDynamic(this, &UInteractable::OnOverlap);
	// ...
	
}


// Called every frame
void UInteractable::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInteractable::Interact()
{
	OnInteractDelegate.Broadcast();
}

void UInteractable::OnOverlap(AActor* OverlappedActor, AActor* OtherActor )
{
	if(OtherActor->ActorHasTag(FName("Player")))
		Interact();
}

