// Shoot Them Up. All Rights Recerved


#include "PickUps/STUBasePickup.h"
#include "Components/SphereComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBasePickup, All, All);

// Sets default values
ASTUBasePickup::ASTUBasePickup()
{
    PrimaryActorTick.bCanEverTick = true;

    CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    CollisionComponent->InitSphereRadius(50.0f);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    SetRootComponent(CollisionComponent);
}

// Called when the game starts or when spawned
void ASTUBasePickup::BeginPlay()
{
    Super::BeginPlay();

    check(CollisionComponent);

    if (PickupMovement.MoveType == EMovementType::Move)
    {
        InitialPickupLocation = GetActorLocation();
        if (PickupMovement.MoveRotationYaw.WannaRandRotationYaw)
        {
            GenerateRotationYaw();
        }
    }
}

// Called every frame
void ASTUBasePickup::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    AllPickupMovement();
}

void ASTUBasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);

    const auto Pawn = Cast<APawn>(OtherActor);
    if (!GivePickupTo(Pawn))
    {
        return;
    }
    PickupWasTaken();
}

bool ASTUBasePickup::GivePickupTo(APawn* PlayerPawn)
{
    return false;
}

void ASTUBasePickup::PickupWasTaken()
{
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    if (GetRootComponent())
    {
        GetRootComponent()->SetVisibility(false, true);
    }
    GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ASTUBasePickup::Respawn, RespawnTime);
}

void ASTUBasePickup::Respawn()
{
    if (PickupMovement.MoveRotationYaw.WannaRandRotationYaw)
    {
        GenerateRotationYaw();
    }
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    if (GetRootComponent())
    {
        GetRootComponent()->SetVisibility(true, true);
    }
}

void ASTUBasePickup::AllPickupMovement()
{
    switch (PickupMovement.MoveType)
    {
    case EMovementType::Move:
    {
        MovementRotationYaw();
        MovementSinZ();
    }
    case EMovementType::Static:
        break;
    default:
        break;
    }
}

void ASTUBasePickup::MovementRotationYaw()
{
    AddActorLocalRotation(FRotator(0.0f, PickupMovement.MoveRotationYaw.RotationYaw, 0.0f));
}

void ASTUBasePickup::GenerateRotationYaw()
{
    const auto Direction = FMath::RandBool() ? 1.0f : -1.0f;
    PickupMovement.MoveRotationYaw.RotationYaw = FMath::RandRange(1.0f, 2.0f) * Direction;
}

void ASTUBasePickup::MovementSinZ()
{
    // z = z0 + amplitude * sin ( Frequence * t);
    FVector CurrentLocation = GetActorLocation();

    if (GetWorld())
    {
        const float Time = GetWorld()->GetTimeSeconds();
        CurrentLocation.Z = InitialPickupLocation.Z + PickupMovement.MoveSinZ.Amplitude * FMath::Sin(
                                PickupMovement.MoveSinZ.Frequence * Time);
        SetActorLocation(CurrentLocation);
    }
}

bool ASTUBasePickup::CouldBeTaken() const
{
    return !GetWorldTimerManager().IsTimerActive(RespawnTimerHandle);
}