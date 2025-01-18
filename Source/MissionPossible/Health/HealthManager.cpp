// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthManager.h"

#include "GameFramework/Character.h"
// Sets default values for this component's properties
UHealthManager::UHealthManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}

void UHealthManager::ChangeHealth(const float& NewHealth)
{
	Health = NewHealth;
	OnHealthChangedDelegate.Broadcast(Health);
}

float UHealthManager::GetHealth() const
{
	return Health;
}

void UHealthManager::ReceiveDamage(const float& DamageAmount)
{
	if (IsDead)
		return;
	if (DamageAmount>Health)
	{
		ChangeHealth(0);
		Cast<ACharacter>(GetOwner())->GetMesh()->SetSimulatePhysics(true);
		OnDeathDelegate.Broadcast();
		IsDead = true;
	}
	else
	{
		ChangeHealth(Health-DamageAmount);
	}
}

void UHealthManager::UseMedKit()
{
	if (HasMedKit())
	{
		MedKitCount--;
		OnMedKitUseDelegate.Broadcast(MedKitCount);
		ChangeHealth(1);
	}
}

int UHealthManager::GetMedKitCount() const
{
	return MedKitCount;
}

bool UHealthManager::HasMedKit()const
{
	return MedKitCount>0;
}

bool UHealthManager::CheckisDead()
{
	return IsDead;
}


// Called when the game starts
void UHealthManager::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHealthManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

