// Shoot Them Up. All Rights Recerved


#include "UI/STUBaseWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

void USTUBaseWidget::Show()
{
    PlayAnimation(ShowAnimation);
    UGameplayStatics::PlaySound2D(GetWorld(), OpenWidgetSound);
}