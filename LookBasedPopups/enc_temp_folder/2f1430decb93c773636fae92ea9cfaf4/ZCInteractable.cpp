#include "LookBasedPopups/ZC/ZCInteractable.h"

#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"

DEFINE_LOG_CATEGORY(ZCInteractableLog)

// Sets default values
AZCInteractable::AZCInteractable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (ProximityTrigger == nullptr)
	{
		ProximityTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("ProximityTrigger"));
		
		// Set debug sphere visible in game
		ProximityTrigger->bHiddenInGame = false;

		// Specify we only want to check overlap and  query collision
		ProximityTrigger->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
		ProximityTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	
		// Attach it to the root
		SetRootComponent(ProximityTrigger);
	}

	if (PopupWidget == nullptr)
	{
		PopupWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("PopupWidget"));
		if (PopupWidget)
		{
			PopupWidget->SetupAttachment(GetRootComponent());
		}
	}
}

// Called when the game starts or when spawned
void AZCInteractable::BeginPlay()
{
	Super::BeginPlay();
	
	// Subscribe for overlap event begin
	if (!ProximityTrigger->OnComponentBeginOverlap.IsBound())
	{
		ProximityTrigger->OnComponentBeginOverlap.AddDynamic(this, &AZCInteractable::OnBeginOverlap);
	}

	// Subscribe for overlap event end
	if (!ProximityTrigger->OnComponentEndOverlap.IsBound())
	{
		ProximityTrigger->OnComponentEndOverlap.AddDynamic(this, &AZCInteractable::OnEndOverlap);
	}
}

void AZCInteractable::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(ZCInteractableLog, Log, TEXT("Began overlapping actor [%d]"), OtherActor ? OtherActor->GetUniqueID() : -1);
}

void AZCInteractable::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(ZCInteractableLog, Log, TEXT("Stopped overlapping actor [%d]"), OtherActor ? OtherActor->GetUniqueID() : -1);
}

// Called every frame
void AZCInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

