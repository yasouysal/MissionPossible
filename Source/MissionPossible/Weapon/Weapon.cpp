// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

#include "Engine/SkeletalMeshSocket.h"
#include "MissionPossible/MissionPossibleCharacter.h"
#include "MissionPossible/Projectile/Projectile.h"
#include "UObject/UnrealTypePrivate.h"

class UIntProperty;
// Sets default values for this component's properties
UWeapon::UWeapon()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UWeapon::BeginPlay()
{
	Super::BeginPlay();


	if(const USkeletalMeshComponent* SkeletalMeshComponent = this->GetOwner()->GetComponentByClass<USkeletalMeshComponent>())
	{
		FirstWeapon = Cast<USkeletalMeshComponent>(SkeletalMeshComponent->GetChildComponent(0));
		SecondWeapon = Cast<USkeletalMeshComponent>(SkeletalMeshComponent->GetChildComponent(1));
	}
	

	if(FirstWeapon)
	{
		FirstWeaponSocket = FirstWeapon->GetSocketByName(FName("projectileSpawnPoint"));
	}

	if(SecondWeapon)
	{
		SecondWeaponSocket = SecondWeapon->GetSocketByName(FName("projectileSpawnPoint"));
	}
}


// Called every frame
void UWeapon::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// if(CoolDown > 0)
	// {
	// 	CoolDown -= 1*DeltaTime;
	// }
}

void UWeapon::Fire()
{
	if(FirstWeaponSocket)
	{
		FirstProjectileSpawnTransform = FirstWeaponSocket->GetSocketTransform(FirstWeapon);
	}

	if(FirstWeaponSocket)
	{
		SecondProjectileSpawnTransform = SecondWeaponSocket->GetSocketTransform(SecondWeapon);
	}
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	AProjectile* SpawnedProjectile;
	AMissionPossibleCharacter* mpc = Cast<AMissionPossibleCharacter>(this->GetOwner());
	if(mpc->characterWeaponState == E_State2::Rifle1 && FWAmmoCount>0)
	{
		SpawnedProjectile = GetWorld()->SpawnActor<AProjectile>(Projectile, FirstProjectileSpawnTransform.GetLocation() , FirstProjectileSpawnTransform.Rotator(), SpawnParams);
		FWAmmoCount--;
		OnFireDelegate.Broadcast(FWAmmoCount,E_State2::Rifle1);
	}
	else if(mpc->characterWeaponState == E_State2::Rifle2 && SWAmmoCount>0)
	{
		SpawnedProjectile = GetWorld()->SpawnActor<AProjectile>(Projectile, SecondProjectileSpawnTransform.GetLocation() , SecondProjectileSpawnTransform.Rotator(), SpawnParams);
		SWAmmoCount--;
		OnFireDelegate.Broadcast(SWAmmoCount,E_State2::Rifle2);
	}
}

int UWeapon::GetAmmo(E_State2 WeaponType)const
{
	switch (WeaponType)
	{
	case E_State2::Rifle1:
		return FWAmmoCount;
	case E_State2::Rifle2:
		return SWAmmoCount;
	default:
		return 0;
	}
}
