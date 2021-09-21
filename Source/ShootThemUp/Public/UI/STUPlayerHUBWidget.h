// Shoot Them Up. All Rights Recerved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUCoreTypes.h"
#include "STUPlayerHUBWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUPlayerHUBWidget : public UUserWidget
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category="UI")
    float GetHealthPercent() const;

    UFUNCTION(BlueprintCallable, Category="UI")
    bool GetCurrentWeaponUIData(FWeaponUIData& UIData) const;

    UFUNCTION(BlueprintCallable, Category="UI")
    bool GetCurrentWeaponAmmoData(FAmmoData& AmmoData, FText& TextAmmoData) const;

    UFUNCTION(BlueprintCallable, Category="UI")
    bool IsPlayerAlive() const;

    UFUNCTION(BlueprintCallable, Category="UI")
    bool IsPlayerSpectating() const;

    UFUNCTION(BlueprintImplementableEvent, Category="UI")
    void OnTakeDamage();

    virtual bool Initialize() override;

    //void MakeHiddenUI();

private:
    void OnHealthChanged(float Health, float HealthDelta);
};
