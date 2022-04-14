#include "LookBasedPopups/ZC/ZCInteractable.h"

#include "Components/SphereComponent.h"

// Sets default values
AZCInteractable::AZCInteractable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (ProximityTrigger == nullptr)
	{
		ProximityTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("ProximityTrigger"));
		SetRootComponent(ProximityTrigger);
	}
}

// Called when the game starts or when spawned
void AZCInteractable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AZCInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

