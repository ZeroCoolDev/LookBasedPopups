#include "LookBasedPopups/ZC/ZCInteractableManager.h"

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

void UZCInteractableManager::ItemEnteredRange(class AActor*)
{

}

void UZCInteractableManager::ItemLeftRange(class AActor*)
{

}

void UZCInteractableManager::CheckForItemsInRange()
{

}

