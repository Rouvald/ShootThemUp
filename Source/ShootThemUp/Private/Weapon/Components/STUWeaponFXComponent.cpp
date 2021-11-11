// Shoot Them Up. All Rights Recerved


#include "Weapon/Components/STUWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "KisMet/GameplayStatics.h"
#include "Components/DecalComponent.h"
#include "Sound/SoundCue.h"

// Sets default values for this component's properties
USTUWeaponFXComponent::USTUWeaponFXComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void USTUWeaponFXComponent::PlayImpactFX(const FHitResult& Hit) const
{
    auto ImpactData = DefaultImpactData;

    if (Hit.PhysMaterial.IsValid())
    {
        const auto PhysMat = Hit.PhysMaterial.Get();
        if (ImpactDataMap.Contains(PhysMat))
        {
            ImpactData = ImpactDataMap[PhysMat];
        }
    }

    // Niagara
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), //
        ImpactData.NiagaraEffect,                              //
        Hit.ImpactPoint,                                       //
        Hit.Normal.Rotation());

    // Decal

    auto DecalComponent = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), //
        ImpactData.DecalData.Material,                 //
        ImpactData.DecalData.Size,                     //
        Hit.ImpactPoint,                               //
        Hit.Normal.Rotation() );
    if (DecalComponent)
    {
        DecalComponent->SetFadeOut(ImpactData.DecalData.Lifetime, ImpactData.DecalData.FadeOut);
    }
    UGameplayStatics::SpawnSoundAtLocation(GetWorld(),ImpactData.ImpactSound, Hit.ImpactPoint);
}
