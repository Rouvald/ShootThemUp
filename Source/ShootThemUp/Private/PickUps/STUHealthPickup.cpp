// Shoot Them Up. All Rights Recerved


#include "PickUps/STUHealthPickup.h"
#include "Components//STUHealthComponent.h"
#include "STUUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthickup, All, All);

bool ASTUHealthPickup::GivePickupTo(APawn* PlayerPawn)
{
    const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(PlayerPawn);
    if (!HealthComponent || HealthComponent->IsDead()) return false;

    return HealthComponent->TryToAddHealth(HealthAmount);
}