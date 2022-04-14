// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ZCInteractable.generated.h"

UCLASS()
class LOOKBASEDPOPUPS_API AZCInteractable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AZCInteractable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// UI Widget that shows the player when they are within range of interacting
	class UWidgetComponent* InteractWidget = nullptr;

	// Proximity trigger to allow interaction (widget popup) or not
	class USphereComponent* ProximityTrigger = nullptr;
};
