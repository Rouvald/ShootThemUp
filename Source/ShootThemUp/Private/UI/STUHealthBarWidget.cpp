// Shoot Them Up. All Rights Recerved


#include "UI/STUHealthBarWidget.h"
#include "Components/ProgressBar.h"

void USTUHealthBarWidget::SetHealthPercent(float HealthPercent)
{
    if (!HealthProgressBar) return;

    const auto HealthBarVisibility = (HealthPercent > PercentVisibilityThreshold || FMath::IsNearlyZero(HealthPercent)) //
                                         ? ESlateVisibility::Hidden                                                     //
                                         : ESlateVisibility::Visible;
    HealthProgressBar->SetVisibility(HealthBarVisibility);

    const auto HealthBarColor = HealthPercent > PercentColorThreshold ? GoodColor : BadColor;
    HealthProgressBar->SetFillColorAndOpacity(HealthBarColor);

    HealthProgressBar->SetPercent(HealthPercent);
}
