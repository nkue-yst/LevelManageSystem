// Copyright 2021 Yoshito Nakaue. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Containers/Array.h"
#include "Engine/LatentActionManager.h"
#include "LevelManageComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LEVELMANAGESYSTEM_API ULevelManageComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULevelManageComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Get list of loaded levels
	UFUNCTION(BlueprintPure)
		TArray<FName> GetLoadedLevels() const { return LoadedLevels; }

	// Called when completed loading level
	UFUNCTION()
		void CompleteLoading() { --LoadingNum; }

	// Load one level
	UFUNCTION(BlueprintCallable)
		void LoadLevel(const FName& Level);

	// Load multiple levels
	UFUNCTION(BlueprintCallable)
		void LoadLevels(const TArray<FName> Levels);

	// Unload one level
	UFUNCTION(BlueprintCallable)
		void UnloadLevel(const FName& Level);

	// Unload multiple levels
	UFUNCTION(BlueprintCallable)
		void UnloadLevels(const TArray<FName> Levels);

private:
	FLatentActionInfo lai;
	int lai_UUID;
	TArray<FLatentActionInfo> LatentActionInfo;

	// List of loaded levels
	UPROPERTY(VisibleAnywhere)
		TArray<FName> LoadedLevels;

	// Loading levels num
	UPROPERTY(VisibleAnywhere)
		int LoadingNum;
};
