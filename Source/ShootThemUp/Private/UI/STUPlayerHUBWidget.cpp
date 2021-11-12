// Shoot Them Up. All Rights Recerved


#include "UI/STUPlayerHUBWidget.h"
#include "Components/STUWeaponComponent.h"
#include "Components/STUHealthComponent.h"
#include "STUUtils.h"
#include "Player/STUBaseCharacter.h"
#include "Components/ProgressBar.h"
#include "Player/STUPlayerState.h"

void USTUPlayerHUBWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (GetOwningPlayer())
    {
        GetOwningPlayer()->GetOnNewPawnNotifier().AddUObject(this, &USTUPlayerHUBWidget::OnNewPawn);
        OnNewPawn(GetOwningPlayerPawn());
    }
}

void USTUPlayerHUBWidget::OnNewPawn(APawn* NewPawn)
{
    const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(NewPawn);
    if (HealthComponent && !HealthComponent->OnHealthChanged.IsBoundToObject(this))
    {
        HealthComponent->OnHealthChanged.AddUObject(this, &USTUPlayerHUBWidget::OnHealthChanged);
    }
    UpdateHealthBar();
}

void USTUPlayerHUBWidget::OnHealthChanged(float Health, float HealthDelta)
{
    if (HealthDelta < 0.0f)
    {
        OnTakeDamage();
        if(!IsPlayingAnimation())
        {
            PlayAnimation(DamageAnimation);
        }
    }
    UpdateHealthBar();
}


float USTUPlayerHUBWidget::GetHealthPercent() const
{
    const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(GetOwningPlayerPawn());
    if (!HealthComponent) return 0.0f;

    return HealthComponent->GetHealthPercent();
}

bool USTUPlayerHUBWidget::GetCurrentWeaponUIData(FWeaponUIData& UIData) const
{
    const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(GetOwningPlayerPawn());
    if (!WeaponComponent) return false;

    return WeaponComponent->GetCurrentWeaponUIData(UIData);
}

bool USTUPlayerHUBWidget::GetCurrentWeaponAmmoData(FAmmoData& AmmoData, FText& TextAmmoData) const
{
    const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(GetOwningPlayerPawn());
    if (!WeaponComponent) return false;

    return WeaponComponent->GetCurrentWeaponAmmoData(AmmoData);
}

bool USTUPlayerHUBWidget::IsPlayerAlive() const
{
    const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(GetOwningPlayerPawn());
    return HealthComponent && !HealthComponent->IsDead();
}

bool USTUPlayerHUBWidget::IsPlayerSpectating() const
{
    const auto Controller = GetOwningPlayer();
    return Controller && Controller->GetStateName() == NAME_Spectating;
}

int32 USTUPlayerHUBWidget::GetKillsNum() const
{
    const auto Controller = GetOwningPlayer();
    if (!Controller) return 0;

    const auto PlayerState = Controller->GetPlayerState<ASTUPlayerState>();
    return PlayerState ? PlayerState->GetKillsNum() : 0;
}

int32 USTUPlayerHUBWidget::GetDeathsNum() const
{
    const auto Controller = GetOwningPlayer();
    if (!Controller) return 0;

    const auto PlayerState = Controller->GetPlayerState<ASTUPlayerState>();
    return PlayerState ? PlayerState->GetDeathsNum() : 0;
}

void USTUPlayerHUBWidget::UpdateHealthBar()
{
    if(HealthProgressBar)
    {
        HealthProgressBar->SetFillColorAndOpacity(GetHealthPercent() > PercentColorThreshold ? GoodColor : BadColor);
    }
}

FString USTUPlayerHUBWidget::FormatBullets(int32 BulletsNum) const
{
    const int32 MaxLen = 3;
    const TCHAR PrefixSymbol = '0';

    auto BulletsStr = FString::FromInt(BulletsNum);
    const auto SymbolNumToAdd = MaxLen-BulletsStr.Len();
    if(SymbolNumToAdd > 0)
    {
        BulletsStr = FString::ChrN(SymbolNumToAdd, PrefixSymbol).Append(BulletsStr);
    }
    return BulletsStr;
}