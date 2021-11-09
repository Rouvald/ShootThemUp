// Shoot Them Up. All Rights Recerved


#include "Menu/UI/STUMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "STUGameInstance.h"
#include "STULevelItemWidget.h"
#include "Components/HorizontalBox.h"
#include "Kismet/KismetSystemLibrary.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUMenuWidget, All, All);

void USTUMenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (StartGameButton)
    {
        StartGameButton->OnClicked.AddDynamic(this, &USTUMenuWidget::OnStartGame);
    }

    if (QuitGameButton)
    {
        QuitGameButton->OnClicked.AddDynamic(this, &USTUMenuWidget::OnQuitGame);
    }
    InitLevelItems();
}

void USTUMenuWidget::InitLevelItems()
{
    const auto STUGameInstance = GetSTUGameInstance();
    if (!STUGameInstance) return;

    checkf(STUGameInstance->GetLevelsData().Num() !=0, TEXT("Levels data is empty"));

    if(!LevelItemsBox) return;
    LevelItemsBox->ClearChildren();

    for( const auto LevelData: STUGameInstance->GetLevelsData())
    {
        const auto LevelItemWidget = CreateWidget<USTULevelItemWidget>(this, LevelItemWidgetClass);
        if(!LevelItemWidget) continue;

        LevelItemWidget->SetLevelData(LevelData);
        LevelItemWidget->OnLevelSelected.AddUObject(this, &USTUMenuWidget::OnLevelSelected);

        LevelItemsBox->AddChild(LevelItemWidget);
        LevelItemWidgets.Add(LevelItemWidget);
    }

    if(STUGameInstance->GetStartLevel().LevelName.IsNone())
    {
        OnLevelSelected(STUGameInstance->GetLevelsData()[0]);
    }else
    {
        OnLevelSelected(STUGameInstance->GetStartLevel());
    }
}

void USTUMenuWidget::OnLevelSelected(const FLevelData& Data)
{
    const auto STUGameInstance = GetSTUGameInstance();
    if (!STUGameInstance) return;

    STUGameInstance->SetStartLevel(Data);

    for (const auto LevelItemWidget : LevelItemWidgets)
    {
        if(LevelItemWidget)
        {
            const auto IsSelected = Data.LevelName == LevelItemWidget->GetLevelData().LevelName;
            LevelItemWidget->SetSelected(IsSelected); 
        }
    }
}

void USTUMenuWidget::OnStartGame()
{
    PlayAnimation(StartLevelAnimation);
}

void USTUMenuWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
    if(Animation != StartLevelAnimation) return;
    
    const auto STUGameInstance = GetSTUGameInstance();
    if (!STUGameInstance) return;

    UGameplayStatics::OpenLevel(this, STUGameInstance->GetStartLevel().LevelName);
}

void USTUMenuWidget::OnQuitGame()
{
    UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}

USTUGameInstance* USTUMenuWidget::GetSTUGameInstance() const
{
    if (!GetWorld()) return nullptr;

    return GetWorld()->GetGameInstance<USTUGameInstance>();
}
