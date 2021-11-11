// Shoot Them Up. All Rights Recerved

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "STULauncherWeapon.generated.h"

class ASTUProjectile;

UCLASS()
class SHOOTTHEMUP_API ASTULauncherWeapon : public ASTUBaseWeapon
{
    GENERATED_BODY()
public:
    virtual void StartFire() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    TSubclassOf<ASTUProjectile> ProjectileClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
    USoundCue* ShootNoAmmoSound;

    virtual void MakeShot() override;
};
