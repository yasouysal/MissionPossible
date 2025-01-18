// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MISSIONPOSSIBLE_API UHealthManager : public UActorComponent
{
	GENERATED_BODY()
	
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHealthChangeCallback,const float&,NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMedKitUseCallback,const int&, NewMedKitCount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathCallback);

public:	
	// Sets default values for this component's properties
	UHealthManager();
	UPROPERTY(BlueprintAssignable,BlueprintCallable)
	FHealthChangeCallback OnHealthChangedDelegate;
	UPROPERTY(BlueprintAssignable,BlueprintCallable)
	FOnDeathCallback OnDeathDelegate;
	UPROPERTY(BlueprintAssignable,BlueprintCallable)
	FMedKitUseCallback OnMedKitUseDelegate;
	
	UFUNCTION()
	void ChangeHealth(const float& NewHealth);

	UFUNCTION(BlueprintCallable)
	float GetHealth()const;
	
	void ReceiveDamage(const float& DamageAmount);
	
	UFUNCTION(BlueprintCallable)
	void UseMedKit();

	UFUNCTION(BlueprintCallable)
	bool CheckisDead();

	UFUNCTION(BlueprintCallable)
	int GetMedKitCount()const;
	
	UFUNCTION()
	bool HasMedKit()const;
	
	UPROPERTY(EditAnywhere)
	int MedKitCount;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
private:
	UPROPERTY()
	float Health = 1;
	UPROPERTY()
	bool IsDead = false;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
		
};
