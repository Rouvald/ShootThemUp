// Shoot Them Up. All Rights Recerved

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "STUCoreTypes.h"
#include "STUGameInstance.generated.h"


class USoundClass;
/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUGameInstance : public UGameInstance
{
    GENERATED_BODY()

public:
    
    FLevelData GetStartLevel() const { return StartLevel; }
    void SetStartLevel(const FLevelData& Data) {StartLevel = Data;}

    TArray<FLevelData> GetLevelsData() const {return LevelsData;}
    
    FName GetMenuLevelName() const { return MenuLevelName; }

    void ToggleVolume();
    
protected:
    UPROPERTY(EditDefaultsOnly, Category="Game", meta=(ToolTip = "Level names must be unique!"))
    TArray<FLevelData> LevelsData;

    UPROPERTY(EditDefaultsOnly, Category="Game")
    FName MenuLevelName = NAME_None;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Sound")
    USoundClass* MasterSoundClass; 

    private:
    FLevelData StartLevel;
};
