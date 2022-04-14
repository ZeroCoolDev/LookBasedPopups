#include "LookBasedPopups/ZC/ZCInteractableManager.h"
#include "LookBasedPopups/LookBasedPopupsCharacter.h"

#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

DEFINE_LOG_CATEGORY(ZCInteractableMgrLog)

// Sets default values for this component's properties
UZCInteractableManager::UZCInteractableManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UZCInteractableManager::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UZCInteractableManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CheckForItemsInRange();
}

void UZCInteractableManager::ItemEnteredRange(class AActor* EnteringActor)
{
	if (EnteringActor)
	{
		// It should never be the case that an item we just came into range with is already in the map
		ensure(ItemsInRange.Find(EnteringActor->GetUniqueID()) == nullptr);
		// Add the item to our map, keyed by the unique ID of the object
		ItemsInRange.FindOrAdd(EnteringActor->GetUniqueID(), MakeWeakObjectPtr<AActor>(EnteringActor));
		UE_LOG(ZCInteractableMgrLog, Log, TEXT("actor [%d] is in range"), EnteringActor->GetUniqueID());
	}
}

void UZCInteractableManager::ItemExitedRange(class AActor* ExitingActor)
{
	if (ExitingActor)
	{
		ItemsInRange.Remove(ExitingActor->GetUniqueID());
		UE_LOG(ZCInteractableMgrLog, Log, TEXT("actor [%d] is out of range"), ExitingActor->GetUniqueID());
	}
}

void UZCInteractableManager::CheckForItemsInRange()
{
	if (ItemsInRange.Num())
	{
		UE_LOG(LogTemp, Warning, TEXT("UZCInteractableManager::CheckForItemsInRange Ticking"));
		ALookBasedPopupsCharacter* OwningChar = Cast<ALookBasedPopupsCharacter>(GetOwner());
		if (ensure(OwningChar))
		{
			FVector CrosshairWorldPos, CrosshairFwdDir;
			if (GetCrosshairWorldPosition(CrosshairWorldPos, CrosshairFwdDir))
			{
				for (auto It = ItemsInRange.CreateConstIterator(); It; ++It)
				{
					const AActor* Item = Cast<AActor>(It->Value);
					if (Item)
					{
						// Draw a line from the player to the item
						DrawDebugLine(GetWorld(), OwningChar->GetActorLocation(), Item->GetActorLocation(), FColor::Green);
					}
				}
			}
		}
	}
}

bool UZCInteractableManager::GetCrosshairWorldPosition(FVector& OutWorldPos, FVector& OutWorldDir)
{
	if (GEngine)
	{
		// Get viewport size
		FVector2D ViewportSize;
		GEngine->GameViewport->GetViewportSize(ViewportSize);

		// Get screen space position of crosshairs
		FVector2D CrosshairScreenPosition(ViewportSize.X / 2.f, ViewportSize.Y / 2.f);
		CrosshairScreenPosition.Y -= 50.f; // Account for the fact that the HUD raised crosshairs a little

		// Get world location and direction of crosshairs
		return UGameplayStatics::DeprojectScreenToWorld(UGameplayStatics::GetPlayerController(this, 0), CrosshairScreenPosition, OutWorldPos, OutWorldDir);
	}
	return false;
}

