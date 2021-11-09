// Shoot Them Up. All Rights Recerved


#include "AI/STUAICharacter.h"
#include "AI/STUAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/STUAIWeaponComponent.h"
#include "BrainComponent.h"
#include "STUHealthComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/STUHealthBarWidget.h"

ASTUAICharacter::ASTUAICharacter(const FObjectInitializer& ObjInit)
    : Super(ObjInit.SetDefaultSubobjectClass<USTUAIWeaponComponent>("WeaponComponent"))
{
    AutoPossessAI = EAutoPossessAI::Disabled;
    AIControllerClass = ASTUAIController::StaticClass();

    bUseControllerRotationYaw = false;
    if (GetCharacterMovement())
    {
        GetCharacterMovement()->bUseControllerDesiredRotation = true;
        GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
    }

    HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("HealthBarWidgetComponent");
    HealthWidgetComponent->SetupAttachment(GetRootComponent());
    HealthWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
    HealthWidgetComponent->SetDrawAtDesiredSize(true);
}

void ASTUAICharacter::BeginPlay()
{
    Super::BeginPlay();

    check(HealthWidgetComponent);

    if (GetWorld())
    {
        GetWorld()->GetTimerManager().SetTimer(CheckHealthWidgetVisibility, this, &ASTUAICharacter::UpdateHealthWidgetVisibility, 0.1f,
            true);
    }
}


void ASTUAICharacter::OnDeath()
{
    Super::OnDeath();

    GetWorld()->GetTimerManager().ClearTimer(CheckHealthWidgetVisibility);

    const auto STUController = Cast<AAIController>(Controller);
    if (STUController && STUController->BrainComponent)
    {
        STUController->BrainComponent->Cleanup();
    }
}

void ASTUAICharacter::OnHealthChanged(float Health, float HealthDelta)
{
    Super::OnHealthChanged(Health, HealthDelta);

    const auto HealthBarWidget = Cast<USTUHealthBarWidget>(HealthWidgetComponent->GetUserWidgetObject());
    if (!HealthBarWidget) return;

    HealthBarWidget->SetHealthPercent(HealthComponent->GetHealthPercent());
}

void ASTUAICharacter::UpdateHealthWidgetVisibility()
{
    if (!GetWorld() ||                             //
        !GetWorld()->GetFirstPlayerController() || //
        !GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator())
        return;

    const auto PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator()->GetActorLocation();
    const auto Distance = FVector::Distance(PlayerLocation, GetActorLocation());
    HealthWidgetComponent->SetVisibility(Distance < HealthWidgetVisibilityDistance, true);
}
