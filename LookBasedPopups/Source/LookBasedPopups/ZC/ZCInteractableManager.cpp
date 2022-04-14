#include "LookBasedPopups/ZC/ZCInteractableManager.h"

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

}

