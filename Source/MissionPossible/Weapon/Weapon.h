// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Weapon.generated.h"

UENUM(BlueprintType) 
enum class E_State2 : uint8
{
	Unarmed UMETA(DisplayName = "Unarmed"),
	Rifle1 UMETA(DisplayName = "Rifle1"),
	Rifle2 UMETA(DisplayName = "Rifle2")
};
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MISSIONPOSSIBLE_API UWeapon : public USceneComponent
{
	GENERATED_BODY()

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnFireCallback, const int&, Count, E_State2, WeaponState);
	
public:	
	// Sets default values for this component's properties
	UWeapon();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void Fire();

	UPROPERTY(BlueprintAssignable,BlueprintAssignable)
	FOnFireCallback OnFireDelegate;

	UFUNCTION(BlueprintCallable)
	int GetAmmo(E_State2 WeaponType)const;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Attributes")
	int FWAmmoCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Attributes")
	int SWAmmoCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Attributes")
	float CoolDown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Attributes")
	float CoolDownValue;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Attributes")
	TSubclassOf<AProjectile> Projectile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Attributes")
	USkeletalMeshComponent* FirstWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Attributes")
	USkeletalMeshComponent* SecondWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Attributes")
	const USkeletalMeshSocket* FirstWeaponSocket;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Attributes")
	const USkeletalMeshSocket* SecondWeaponSocket;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapon Attributes")
	FTransform FirstProjectileSpawnTransform;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapon Attributes")
	FTransform SecondProjectileSpawnTransform;

};
