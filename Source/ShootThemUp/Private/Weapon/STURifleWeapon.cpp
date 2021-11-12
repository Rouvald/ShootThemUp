// Shoot Them Up. All Rights Recerved

#include "Weapon/STURifleWeapon.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Weapon/Components/STUWeaponFXComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "STUPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"

ASTURifleWeapon::ASTURifleWeapon()
{
    WeaponFXComponent = CreateDefaultSubobject<USTUWeaponFXComponent>("WeaponFXComponent");
}

void ASTURifleWeapon::BeginPlay()
{
    Super::BeginPlay();

    check(WeaponFXComponent);
}


void ASTURifleWeapon::StartFire()
{
    InitFx();
    GetWorldTimerManager().SetTimer(ShootTimerHandle, this, &ASTURifleWeapon::MakeShot, TimeBetweenShots, true);
    MakeShot();
}

void ASTURifleWeapon::StopFire()
{
    GetWorldTimerManager().ClearTimer(ShootTimerHandle);
    SetFXActive(false);
}

void ASTURifleWeapon::MakeShot()
{
    if (!GetWorld() || IsAmmoEmpty())
    {
        StopFire();
        return;
    }
    FVector TraceStart, TraceEnd;
    if (!GetTraceData(TraceStart, TraceEnd))
    {
        StopFire();
        return;
    }

    FHitResult HitResult;
    MakeHit(HitResult, TraceStart, TraceEnd);

    FVector TraceFXEnd = TraceEnd;
    if (HitResult.bBlockingHit)
    {
        TraceFXEnd = HitResult.ImpactPoint;
        MakeDamage(HitResult);
        //DrawDebugLine(GetWorld(), GetMuzzleworldLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.0f, 0, 3.0f);
        //DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 32, FColor::Red, false, 5.0f);
        /*UGameplayStatics::ApplyPointDamage(
           HitResult.GetActor(), Damage, HitResult.ImpactPoint, HitResult, GetPlayerController(), GetOwner(), nullptr);*/
        WeaponFXComponent->PlayImpactFX(HitResult);
    }
    /*else
    {
        DrawDebugLine(GetWorld(), GetMuzzleworldLocation(), TraceEnd, FColor::Red, false, 3.0f, 0, 3.0f);
    }*/
    SpawnTraceFX(GetMuzzleWorldLocation(), TraceFXEnd);
    DecreaseAmmo();
}

bool ASTURifleWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
    FVector ViewLocation;
    FRotator ViewRotation;

    if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;
    TraceStart = ViewLocation;
    const auto HalfRad = FMath::DegreesToRadians(BulletSpread);
    const FVector ShootDiraction = FMath::VRandCone(ViewRotation.Vector(), HalfRad);
    TraceEnd = TraceStart + ShootDiraction * TraceMaxDistance;
    return true;
}

void ASTURifleWeapon::MakeDamage(FHitResult& HitResult)
{
    const auto DamagedActor = HitResult.GetActor();
    if (!DamagedActor) return;

    FPointDamageEvent PointDamageEvent;
    PointDamageEvent.HitInfo = HitResult;
    DamagedActor->TakeDamage(Damage, PointDamageEvent, GetController(), this);
}


void ASTURifleWeapon::InitFx()
{
    if (!MuzzleFXComponent)
    {
        MuzzleFXComponent = SpawnMuzzleFX();
    }
    if (!ShootAudioComponent)
    {
        ShootAudioComponent = UGameplayStatics::SpawnSoundAttached(ShootSound, WeaponMesh, MuzzleSocketName);
    }
    SetFXActive(true);
}

void ASTURifleWeapon::SetFXActive(bool IsActive) const
{
    if (MuzzleFXComponent)
    {
        MuzzleFXComponent->SetPaused(!IsActive);
        MuzzleFXComponent->SetVisibility(IsActive, true);
    }
    if (ShootAudioComponent)
    {
        ShootAudioComponent->SetPaused(!IsActive);
    }
}

void ASTURifleWeapon::SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd)
{
    const auto TraceFXComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), TraceFX, TraceStart);
    if (TraceFXComponent)
    {
        TraceFXComponent->SetNiagaraVariableVec3(TraceTargetName, TraceEnd);
    }
}

AController* ASTURifleWeapon::GetController() const
{
    const auto Pawn = Cast<APawn>(GetOwner());
    return Pawn ? Pawn->GetController() : nullptr;
}

void ASTURifleWeapon::Zoom(bool Enable)
{
    const auto PlayerController = Cast<ASTUPlayerController>(GetController());
    if (!PlayerController || !PlayerController->PlayerCameraManager) return;

    if(Enable)
    {
        FOVDefaultAngle = PlayerController->PlayerCameraManager->GetFOVAngle();
    }
    PlayerController->PlayerCameraManager->SetFOV(Enable ? FOVZoomAngle : FOVDefaultAngle);
}
