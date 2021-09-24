// Shoot Them Up. All Rights Recerved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUCoreTypes.h"
#include "STUWeaponComponent.generated.h"

class ASTUBaseWeapon;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTTHEMUP_API USTUWeaponComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USTUWeaponComponent();

    virtual void StartFire();
    void StopFire();
    virtual void NextWeapon();
    void Reload();

    bool GetCurrentWeaponUIData(FWeaponUIData& UIData) const;
    bool GetCurrentWeaponAmmoData(FAmmoData& AmmoData, FText& TextAmmoData) const;

    bool TryToAddAmmo(TSubclassOf<ASTUBaseWeapon> WeaponType, int32 ClipsAmount);
    bool NeedAmmo(TSubclassOf<ASTUBaseWeapon> WeaponType);

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    TArray<FWeaponData> WeaponData;

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponEquipSocketName = "WeaponSocket";

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponArmorySocketName = "ArmorySocket";

    UPROPERTY(EditDefaultsOnly, Category = "Animation")
    UAnimMontage* EquipAnimMontage;

    UPROPERTY()
    ASTUBaseWeapon* CurrentWeapon = nullptr;

    UPROPERTY()
    TArray<ASTUBaseWeapon*> Weapons;

    int32 CurrentWeaponIndex = 0;

    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

    bool CanEquip() const;
    bool CanFire() const;
    void Equipweapon(int32 WeaponIndex);
    
private:
    UPROPERTY()
    UAnimMontage* CurrentReloadAnimMontage = nullptr;
    
    bool EquipAnimInProgress = false;
    bool ReloadAnimInProgress = false;

    void InitAnimation();
    void SpawnWeapons();
    void AttachWeaponToSocket(ASTUBaseWeapon* Weapon, USceneComponent* SceneComponent, FName& WeaponName);

    void PlayAnimMontage(UAnimMontage* Animation);

    void OnEquipFinished(USkeletalMeshComponent* MeshComp);
    void OnReloadFinished(USkeletalMeshComponent* MeshComp);

   bool CanReload() const;

    void OnEmptyClip(ASTUBaseWeapon* AmmoEmptyweapon);
    void ChangeClip();
};
