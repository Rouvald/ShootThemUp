// Shoot Them Up. All Rights Recerved

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "STUCoreTypes.h"
#include "STUBasePickup.generated.h"

class USphereComponent;


UCLASS()
class SHOOTTHEMUP_API ASTUBasePickup : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ASTUBasePickup();

protected:
    UPROPERTY(VisibleAnywhere, Category= "Pickup")
    USphereComponent* CollisionComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Pickup")
    float RespawnTime = 5.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "PickupMovement")
    FPickupMovement PickupMovement;

    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
    bool CouldBeTaken() const;

private:
    FVector InitialPickupLocation;
    FTimerHandle RespawnTimerHandle; 

    virtual bool GivePickupTo(APawn* PlayerPawn);

    void PickupWasTaken();
    void Respawn();

    void AllPickupMovement();
    void MovementRotationYaw();
    void GenerateRotationYaw();
    void MovementSinZ();
};
