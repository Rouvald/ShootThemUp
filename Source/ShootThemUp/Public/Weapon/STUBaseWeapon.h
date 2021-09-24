// Shoot Them Up. All Rights Recerved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUCoreTypes.h"
#include "STUBaseWeapon.generated.h"

class USkeletalMeshComponent;
class UNiagaraSystem;
class UNiagaraComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUBaseWeapon : public AActor
{
    GENERATED_BODY()

public:
    ASTUBaseWeapon();

    FOnClipEmtySignature OnClipEmpty;

    virtual void StartFire();
    virtual void StopFire();

    void ChangeClip();
    bool CanReload();
    bool IsAmmoEmpty() const;

    FWeaponUIData GetUIData() const { return UIData; }
    FAmmoData GetAmmoData() const { return CurrentAmmo; }

    bool TryToAddAmmo(int32 ClipsAmount);
    
    FText GetTextWeaponAmmoData() const;
    bool IsAmmoFull() const;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
    USkeletalMeshComponent* WeaponMesh;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    FName MuzzleSocketName = "MuzzleSocket";

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float TraceMaxDistance = 3000.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    FAmmoData DefaultAmmo{10, 5, false};

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    FWeaponUIData UIData;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    UNiagaraSystem* MuzzleFX;
    
    virtual void BeginPlay() override;

    virtual void MakeShot();
    virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;

    APlayerController* GetPlayerController() const;
    bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
    FVector GetMuzzleworldLocation() const;
    void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);
    //void MakeDamage(FHitResult& HitResult);

    void DecreaseAmmo();
    bool IsClipEmpty() const;
    
    void LogAmmo();

    UNiagaraComponent* SpawnMuzzleFX();
private:
    FAmmoData CurrentAmmo;
};
