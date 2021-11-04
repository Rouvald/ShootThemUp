// Shoot Them Up. All Rights Recerved

#include "Components/STUCharacterMovementComponent.h"
#include "Player/STUBaseCharacter.h"

float USTUCharacterMovementComponent::GetMaxSpeed() const
{
    const float MaxSpeed = Super::GetMaxSpeed();
    const ASTUBaseCharacter* PLayer = Cast<ASTUBaseCharacter>(GetPawnOwner());
    return PLayer && PLayer->IsRunning() /*&& !PLayer->IsCrouching()*/ ? MaxSpeed * RunModifier : MaxSpeed;
}
