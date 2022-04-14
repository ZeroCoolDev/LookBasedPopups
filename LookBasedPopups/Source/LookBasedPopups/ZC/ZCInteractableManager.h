// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ZCInteractableManager.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(ZCInteractableMgrLog, Log, All)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOOKBASEDPOPUPS_API UZCInteractableManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UZCInteractableManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Add the item which entered range to our item range map
	void ItemEnteredRange(class AActor* EnteringActor);

	// Remove the item which left range from our item range map
	void ItemExitedRange(class AActor* ExitingActor);

private:
	void CheckForItemsInRange();

	// Keeps a running list of all items currently in range
	UPROPERTY()
	TMap<uint32, TWeakObjectPtr<class AActor>> ItemsInRange;
	
	// Threshold for how close the player needs to be looking at the item (1 = exactly at it, 0.5 = 50% between looking and not, 0 = looking perpendicular to it)
	UPROPERTY()
	float ItemPopupVisibilityThreshold = 0.99f;
};
