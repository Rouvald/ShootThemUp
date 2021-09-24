// Shoot Them Up. All Rights Recerved


#include "AI/Services/STUChangeWeaponService.h"

#include "AIController.h"
#include "Components/STUWeaponComponent.h"
#include "AIController.h"
#include "STUUtils.h"


USTUChangeWeaponService::USTUChangeWeaponService()
{
    NodeName = "Change Weapon";
}

void USTUChangeWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    const auto Controller = OwnerComp.GetAIOwner();
    if (Controller)
    {
        const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(Controller->GetPawn());
        if(WeaponComponent && Probability > 0.0f && FMath::FRand() <= Probability)
        {
            WeaponComponent->NextWeapon();
        }
    }

    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
