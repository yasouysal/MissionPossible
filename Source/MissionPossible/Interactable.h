// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interactable.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MISSIONPOSSIBLE_API UInteractable : public UActorComponent
{
	GENERATED_BODY()

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInteractCallback);
	
public:	
	// Sets default values for this component's properties
	UInteractable();
	UPROPERTY(BlueprintAssignable)
	FInteractCallback OnInteractDelegate;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
	void Interact();
	UFUNCTION()
	void OnOverlap(AActor* OverlappedActor, AActor* OtherActor );
};
