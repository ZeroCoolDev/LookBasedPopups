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

	// ...
}

void UZCInteractableManager::ItemEnteredRange(class AActor* EnteringActor)
{
	UE_LOG(LogTemp, Log, TEXT("actor [%d] is in range"), EnteringActor ? EnteringActor->GetUniqueID() : -1);
}

void UZCInteractableManager::ItemExitedRange(class AActor* ExitingActor)
{
	UE_LOG(LogTemp, Log, TEXT("actor [%d] is out of range"), ExitingActor ? ExitingActor->GetUniqueID() : -1);
}

void UZCInteractableManager::CheckForItemsInRange()
{

}

