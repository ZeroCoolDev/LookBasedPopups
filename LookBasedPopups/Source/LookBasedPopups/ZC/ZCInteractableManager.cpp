#include "LookBasedPopups/ZC/ZCInteractableManager.h"
#include "LookBasedPopups/ZC/ZCInteractable.h"
#include "LookBasedPopups/LookBasedPopupsCharacter.h"

#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

DEFINE_LOG_CATEGORY(ZCInteractableMgrLog)

// Used for getting the player controller (need to pass in an index)
#ifndef LOCAL_USER_NUM
#define LOCAL_USER_NUM 0
#endif // LOCAL_USER_NUM

#ifndef VECTOR_MULTIPLIER
#define VECTOR_MULTIPLIER 50'000
#endif // VECTOR_MULTIPLIER

#ifndef DRAW_DEBUG
#define DRAW_DEBUG 1
#endif // DRAW_DEBUG


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
	}
}

void UZCInteractableManager::ItemExitedRange(class AActor* ExitingActor)
{
	if (ExitingActor)
	{
		ItemsInRange.Remove(ExitingActor->GetUniqueID());
	}
}

void UZCInteractableManager::CheckForItemsInRange()
{
	if (ItemsInRange.Num())
	{
		ALookBasedPopupsCharacter* OwningChar = Cast<ALookBasedPopupsCharacter>(GetOwner());
		if (ensure(OwningChar))
		{
			FVector CrosshairWorldPos, CrosshairFwdDir;
			if (GetCrosshairWorldPosition(CrosshairWorldPos, CrosshairFwdDir))
			{			
				// Get the player look dir (will be the same for every item this frame so no need to calculate it each loop iteration)
				const FVector PlayerLookDir = CrosshairWorldPos + CrosshairFwdDir * VECTOR_MULTIPLIER;

				for (auto It = ItemsInRange.CreateConstIterator(); It; ++It)
				{
					AZCInteractable* InteractableItem = Cast<AZCInteractable>(It->Value);
					if (InteractableItem)
					{
						// Get the player look dir
						const FVector DirectionToItem = InteractableItem->GetActorLocation() - CrosshairWorldPos;

						// Dot Product will be 1 = parallel, 0 = perpendicular, -1 = opposite
						// So between 0->1 that means we're looking at it (at least some amount)
						float LookAtItemAmount = FVector::DotProduct(PlayerLookDir.GetSafeNormal(), DirectionToItem.GetSafeNormal());

						// If the two vectors are close enough to the point we consider the player looking at the item, show the popup. Otherwise hide it
						bool bPopupShouldBeVisible = LookAtItemAmount >= ItemPopupVisibilityThreshold;

					#if DRAW_DEBUG
						// Draw a line from the player to the item
						DrawDebugLine(GetWorld(), OwningChar->GetActorLocation(), InteractableItem->GetActorLocation(), FColor::Red);
						// Draw a line from the crosshair to item 
						DrawDebugLine(GetWorld(), CrosshairWorldPos, CrosshairWorldPos + DirectionToItem * VECTOR_MULTIPLIER, FColor::Blue);
						// Draw a line representing the players look dir
						DrawDebugLine(GetWorld(), CrosshairWorldPos, PlayerLookDir, bPopupShouldBeVisible ? FColor::Green : FColor::White);
					#endif// DRAW_DEBUG

						// Set the popup visibility on the Interactable based off our look direction
						InteractableItem->SetPopupVisibility(bPopupShouldBeVisible);
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
		return UGameplayStatics::DeprojectScreenToWorld(UGameplayStatics::GetPlayerController(this, LOCAL_USER_NUM), CrosshairScreenPosition, OutWorldPos, OutWorldDir);
	}
	return false;
}

